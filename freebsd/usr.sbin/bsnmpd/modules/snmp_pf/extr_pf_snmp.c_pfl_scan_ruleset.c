#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct pfl_entry {scalar_t__ index; int /*<<< orphan*/ * pkts; int /*<<< orphan*/ * bytes; int /*<<< orphan*/  evals; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {char* label; int /*<<< orphan*/ * packets; int /*<<< orphan*/ * bytes; int /*<<< orphan*/  evaluations; int /*<<< orphan*/  action; } ;
struct pfioc_rule {scalar_t__ nr; TYPE_1__ rule; int /*<<< orphan*/  anchor; } ;
typedef  int /*<<< orphan*/  pr ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETRULE ; 
 int /*<<< orphan*/  DIOCGETRULES ; 
 size_t IN ; 
 int /*<<< orphan*/  LOG_ERR ; 
 size_t OUT ; 
 int /*<<< orphan*/  PF_PASS ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pfl_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct pfioc_rule*,int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_rule*) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pfl_table ; 
 scalar_t__ pfl_table_count ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfl_scan_ruleset(const char *path)
{
	struct pfioc_rule pr;
	struct pfl_entry *e;
	u_int32_t nr, i;

	bzero(&pr, sizeof(pr));
	strlcpy(pr.anchor, path, sizeof(pr.anchor));
	pr.rule.action = PF_PASS;
	if (ioctl(dev, DIOCGETRULES, &pr)) {
		syslog(LOG_ERR, "pfl_scan_ruleset: ioctl(DIOCGETRULES): %s",
		    strerror(errno));
		goto err;
	}

	for (nr = pr.nr, i = 0; i < nr; i++) {
		pr.nr = i;
		if (ioctl(dev, DIOCGETRULE, &pr)) {
			syslog(LOG_ERR, "pfl_scan_ruleset: ioctl(DIOCGETRULE):"
			    " %s", strerror(errno));
			goto err;
		}

		if (pr.rule.label[0]) {
			e = (struct pfl_entry *)malloc(sizeof(*e));
			if (e == NULL)
				goto err;

			strlcpy(e->name, path, sizeof(e->name));
			if (path[0])
				strlcat(e->name, "/", sizeof(e->name));
			strlcat(e->name, pr.rule.label, sizeof(e->name));

			e->evals = pr.rule.evaluations;
			e->bytes[IN] = pr.rule.bytes[IN];
			e->bytes[OUT] = pr.rule.bytes[OUT];
			e->pkts[IN] = pr.rule.packets[IN];
			e->pkts[OUT] = pr.rule.packets[OUT];
			e->index = ++pfl_table_count;

			TAILQ_INSERT_TAIL(&pfl_table, e, link);
		}
	}

	return (0);

err:
	return (-1);
}