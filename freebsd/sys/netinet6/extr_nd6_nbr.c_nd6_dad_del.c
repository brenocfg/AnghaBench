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
struct dadq {int dad_ondadq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DADQ_WLOCK () ; 
 int /*<<< orphan*/  DADQ_WUNLOCK () ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct dadq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_dadq ; 
 int /*<<< orphan*/  dad_list ; 
 int /*<<< orphan*/  nd6_dad_rele (struct dadq*) ; 

__attribute__((used)) static void
nd6_dad_del(struct dadq *dp)
{

	DADQ_WLOCK();
	if (dp->dad_ondadq) {
		/*
		 * Remove dp from the dadq and release the dadq's
		 * reference.
		 */
		TAILQ_REMOVE(&V_dadq, dp, dad_list);
		dp->dad_ondadq = false;
		DADQ_WUNLOCK();
		nd6_dad_rele(dp);
	} else
		DADQ_WUNLOCK();
}