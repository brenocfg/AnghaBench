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
struct uni_sap {int dummy; } ;
struct ccuser {scalar_t__ state; int /*<<< orphan*/  sap; } ;

/* Variables and functions */
 scalar_t__ USER_IN_PREPARING ; 
 scalar_t__ USER_IN_WAITING ; 
 scalar_t__ unisve_overlap_sap (int /*<<< orphan*/ ,struct uni_sap*) ; 

__attribute__((used)) static int
check_overlap(struct ccuser *user, struct uni_sap *sap)
{
	return ((user->state == USER_IN_PREPARING ||
	    user->state == USER_IN_WAITING) &&
	    unisve_overlap_sap(user->sap, sap));
}