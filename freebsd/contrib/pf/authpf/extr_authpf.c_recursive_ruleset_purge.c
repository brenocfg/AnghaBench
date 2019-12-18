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
struct pfioc_trans_e {int size; int esize; int rs_num; char* anchor; char* path; int nr; char* name; struct pfioc_trans_e* array; } ;
struct pfioc_trans {int size; int esize; int rs_num; char* anchor; char* path; int nr; char* name; struct pfioc_trans* array; } ;
struct pfioc_ruleset {int size; int esize; int rs_num; char* anchor; char* path; int nr; char* name; struct pfioc_ruleset* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETRULESET ; 
 int /*<<< orphan*/  DIOCGETRULESETS ; 
 int /*<<< orphan*/  DIOCXBEGIN ; 
 int /*<<< orphan*/  DIOCXCOMMIT ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int PF_RULESET_MAX ; 
 int PF_RULESET_TABLE ; 
 struct pfioc_trans_e* calloc (int,int) ; 
 int /*<<< orphan*/  dev ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct pfioc_trans_e*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_trans_e*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
recursive_ruleset_purge(char *an, char *rs)
{
	struct pfioc_trans_e     *t_e = NULL;
	struct pfioc_trans	 *t = NULL;
	struct pfioc_ruleset	 *prs = NULL;
	int			  i;


	/* purge rules */
	errno = 0;
	if ((t = calloc(1, sizeof(struct pfioc_trans))) == NULL)
		goto no_mem;
	if ((t_e = calloc(PF_RULESET_MAX+1,
	    sizeof(struct pfioc_trans_e))) == NULL)
		goto no_mem;
	t->size = PF_RULESET_MAX+1;
	t->esize = sizeof(struct pfioc_trans_e);
	t->array = t_e;
	for (i = 0; i < PF_RULESET_MAX+1; ++i) {
		t_e[i].rs_num = i;
		snprintf(t_e[i].anchor, sizeof(t_e[i].anchor), "%s/%s", an, rs);
	}
	t_e[PF_RULESET_MAX].rs_num = PF_RULESET_TABLE;
	if ((ioctl(dev, DIOCXBEGIN, t) ||
	    ioctl(dev, DIOCXCOMMIT, t)) &&
	    errno != EINVAL)
		goto cleanup;

	/* purge any children */
	if ((prs = calloc(1, sizeof(struct pfioc_ruleset))) == NULL)
		goto no_mem;
	snprintf(prs->path, sizeof(prs->path), "%s/%s", an, rs);
	if (ioctl(dev, DIOCGETRULESETS, prs)) {
		if (errno != EINVAL)
			goto cleanup;
		errno = 0;
	} else {
		int nr = prs->nr;

		while (nr) {
			prs->nr = 0;
			if (ioctl(dev, DIOCGETRULESET, prs))
				goto cleanup;

			if (recursive_ruleset_purge(prs->path, prs->name))
				goto cleanup;
			nr--;
		}
	}

no_mem:
	if (errno == ENOMEM)
		syslog(LOG_ERR, "calloc failed");

cleanup:
	free(t);
	free(t_e);
	free(prs);
	return (errno);
}