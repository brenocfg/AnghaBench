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
struct in_multi_head {int dummy; } ;
struct in_multi {scalar_t__ inm_refcount; TYPE_1__* inm_ifma; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ifma_protospec; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_MULTI_LIST_LOCK_ASSERT () ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  SLIST_INIT (struct in_multi_head*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct in_multi_head*,struct in_multi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inm_disconnect (struct in_multi*) ; 
 int /*<<< orphan*/  inm_nrele ; 
 int /*<<< orphan*/  inm_release_list_deferred (struct in_multi_head*) ; 

void
inm_release_deferred(struct in_multi *inm)
{
	struct in_multi_head tmp;

	IN_MULTI_LIST_LOCK_ASSERT();
	MPASS(inm->inm_refcount > 0);
	if (--inm->inm_refcount == 0) {
		SLIST_INIT(&tmp);
		inm_disconnect(inm);
		inm->inm_ifma->ifma_protospec = NULL;
		SLIST_INSERT_HEAD(&tmp, inm, inm_nrele);
		inm_release_list_deferred(&tmp);
	}
}