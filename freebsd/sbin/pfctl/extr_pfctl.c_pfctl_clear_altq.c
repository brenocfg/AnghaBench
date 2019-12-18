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
typedef  int /*<<< orphan*/  t ;
struct pfr_buffer {int /*<<< orphan*/  pfrb_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCXBEGIN ; 
 int /*<<< orphan*/  DIOCXCOMMIT ; 
 int /*<<< orphan*/  PFRB_TRANS ; 
 int PF_OPT_QUIET ; 
 int /*<<< orphan*/  PF_RULESET_ALTQ ; 
 int /*<<< orphan*/  altqsupport ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct pfr_buffer*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pfctl_add_trans (struct pfr_buffer*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pfctl_trans (int,struct pfr_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
pfctl_clear_altq(int dev, int opts)
{
	struct pfr_buffer t;

	if (!altqsupport)
		return (-1);
	memset(&t, 0, sizeof(t));
	t.pfrb_type = PFRB_TRANS;
	if (pfctl_add_trans(&t, PF_RULESET_ALTQ, "") ||
	    pfctl_trans(dev, &t, DIOCXBEGIN, 0) ||
	    pfctl_trans(dev, &t, DIOCXCOMMIT, 0))
		err(1, "pfctl_clear_altq");
	if ((opts & PF_OPT_QUIET) == 0)
		fprintf(stderr, "altq cleared\n");
	return (0);
}