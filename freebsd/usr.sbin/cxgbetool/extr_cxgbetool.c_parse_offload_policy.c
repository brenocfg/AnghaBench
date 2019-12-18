#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct t4_offload_policy {int nrules; struct offload_rule* rule; } ;
struct offload_rule {int dummy; } ;
typedef  int /*<<< orphan*/  pcap_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_EN10MB ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ REALLOC_STRIDE ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_offload_policy (struct t4_offload_policy*) ; 
 size_t getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty_line (char*,size_t) ; 
 int parse_offload_policy_line (int,char*,size_t,int /*<<< orphan*/ *,struct offload_rule*) ; 
 int /*<<< orphan*/  pcap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcap_open_dead (int /*<<< orphan*/ ,int) ; 
 struct offload_rule* realloc (struct offload_rule*,int) ; 
 int /*<<< orphan*/  warn (char*,char const*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
parse_offload_policy(const char *fname, struct t4_offload_policy *op)
{
	FILE *fp;
	char *line;
	int lno, maxrules, rc;
	size_t lcap, llen;
	struct offload_rule *r;
	pcap_t *pd;

	fp = fopen(fname, "r");
	if (fp == NULL) {
		warn("Unable to open file \"%s\"", fname);
		return (errno);
	}
	pd = pcap_open_dead(DLT_EN10MB, 128);
	if (pd == NULL) {
		warnx("Failed to open pcap device");
		fclose(fp);
		return (EIO);
	}

	rc = 0;
	lno = 0;
	lcap = 0;
	maxrules = 0;
	op->nrules = 0;
	op->rule = NULL;
	line = NULL;

	while ((llen = getline(&line, &lcap, fp)) != -1) {
		lno++;

		/* Skip empty lines. */
		if (isempty_line(line, llen))
			continue;

		if (op->nrules == maxrules) {
			maxrules += REALLOC_STRIDE;
			r = realloc(op->rule,
			    maxrules * sizeof(struct offload_rule));
			if (r == NULL) {
				warnx("failed to allocate memory for %d rules",
				    maxrules);
				rc = ENOMEM;
				goto done;
			}
			op->rule = r;
		}

		r = &op->rule[op->nrules];
		rc = parse_offload_policy_line(lno, line, llen, pd, r);
		if (rc != 0) {
			warnx("Error parsing line %d of \"%s\"", lno, fname);
			goto done;
		}

		op->nrules++;
	}
	free(line);

	if (!feof(fp)) {
		warn("Error while reading from file \"%s\" at line %d",
		    fname, lno);
		rc = errno;
		goto done;
	}

	if (op->nrules == 0) {
		warnx("No valid rules found in \"%s\"", fname);
		rc = EINVAL;
	}
done:
	pcap_close(pd);
	fclose(fp);
	if (rc != 0) {
		free_offload_policy(op);
	}

	return (rc);
}