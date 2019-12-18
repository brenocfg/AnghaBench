#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct TYPE_3__ {int action; int /*<<< orphan*/  rpool; } ;
struct pfioc_rule {scalar_t__ nr; TYPE_1__ rule; int /*<<< orphan*/  anchor_call; int /*<<< orphan*/  ticket; int /*<<< orphan*/  anchor; } ;
typedef  int /*<<< orphan*/  pr ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETRULE ; 
 int /*<<< orphan*/  DIOCGETRULES ; 
#define  PF_BINAT 130 
#define  PF_NAT 129 
 int PF_OPT_NUMERIC ; 
 int PF_OPT_SHOWALL ; 
 int PF_OPT_VERBOSE2 ; 
#define  PF_RDR 128 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_rule*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct pfioc_rule*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfctl_clear_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ pfctl_get_pool (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  pfctl_print_rule_counters (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pfctl_print_title (char*) ; 
 int /*<<< orphan*/  print_rule (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
pfctl_show_nat(int dev, int opts, char *anchorname)
{
	struct pfioc_rule pr;
	u_int32_t mnr, nr;
	static int nattype[3] = { PF_NAT, PF_RDR, PF_BINAT };
	int i, dotitle = opts & PF_OPT_SHOWALL;

	memset(&pr, 0, sizeof(pr));
	memcpy(pr.anchor, anchorname, sizeof(pr.anchor));
	for (i = 0; i < 3; i++) {
		pr.rule.action = nattype[i];
		if (ioctl(dev, DIOCGETRULES, &pr)) {
			warn("DIOCGETRULES");
			return (-1);
		}
		mnr = pr.nr;
		for (nr = 0; nr < mnr; ++nr) {
			pr.nr = nr;
			if (ioctl(dev, DIOCGETRULE, &pr)) {
				warn("DIOCGETRULE");
				return (-1);
			}
			if (pfctl_get_pool(dev, &pr.rule.rpool, nr,
			    pr.ticket, nattype[i], anchorname) != 0)
				return (-1);
			if (dotitle) {
				pfctl_print_title("TRANSLATION RULES:");
				dotitle = 0;
			}
			print_rule(&pr.rule, pr.anchor_call,
			    opts & PF_OPT_VERBOSE2, opts & PF_OPT_NUMERIC);
			printf("\n");
			pfctl_print_rule_counters(&pr.rule, opts);
			pfctl_clear_pool(&pr.rule.rpool);
		}
	}
	return (0);
}