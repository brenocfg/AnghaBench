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
struct ieee80211vap {struct aclstate* iv_as; } ;
struct aclstate {int as_policy; } ;

/* Variables and functions */

__attribute__((used)) static int
acl_getpolicy(struct ieee80211vap *vap)
{
	struct aclstate *as = vap->iv_as;

	return as->as_policy;
}