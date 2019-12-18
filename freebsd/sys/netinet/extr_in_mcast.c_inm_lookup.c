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
struct in_multi {int dummy; } ;
struct in_addr {int dummy; } ;
struct ifnet {int dummy; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_MULTI_LIST_LOCK_ASSERT () ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 struct in_multi* inm_lookup_locked (struct ifnet*,struct in_addr const) ; 

struct in_multi *
inm_lookup(struct ifnet *ifp, const struct in_addr ina)
{
	struct epoch_tracker et;
	struct in_multi *inm;

	IN_MULTI_LIST_LOCK_ASSERT();
	NET_EPOCH_ENTER(et);

	inm = inm_lookup_locked(ifp, ina);
	NET_EPOCH_EXIT(et);

	return (inm);
}