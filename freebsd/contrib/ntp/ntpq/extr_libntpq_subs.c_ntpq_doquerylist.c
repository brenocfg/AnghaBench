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
typedef  int /*<<< orphan*/  u_short ;
struct varlist {int dummy; } ;
struct ntpq_varlist {int dummy; } ;
typedef  int /*<<< orphan*/  associd_t ;

/* Variables and functions */
 int doquerylist (struct varlist*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t*,char const**) ; 

int
ntpq_doquerylist(
	struct ntpq_varlist *vlist,
	int op,
	associd_t associd,
	int auth,
	u_short *rstatus,
	size_t *dsize,
	const char **datap
	)
{
	return doquerylist((struct varlist *)vlist, op, associd, auth,
			   rstatus, dsize, datap);
}