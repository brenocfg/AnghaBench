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
struct dadq {int /*<<< orphan*/  dad_ifa; int /*<<< orphan*/  dad_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IP6NDP ; 
 int /*<<< orphan*/  free (struct dadq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifa_free (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nd6_dad_rele(struct dadq *dp)
{

	if (refcount_release(&dp->dad_refcnt)) {
		ifa_free(dp->dad_ifa);
		free(dp, M_IP6NDP);
	}
}