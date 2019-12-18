#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  TYPE_2__* sessp ;
typedef  TYPE_3__* priv_p ;
struct TYPE_9__ {TYPE_1__* sesshash; } ;
struct TYPE_8__ {int /*<<< orphan*/  Session_ID; int /*<<< orphan*/  hook; } ;
struct TYPE_7__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_3__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 size_t SESSHASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sessions ; 

__attribute__((used)) static void
pppoe_addsession(sessp sp)
{
	const priv_p	privp = NG_NODE_PRIVATE(NG_HOOK_NODE(sp->hook));
	uint16_t	hash = SESSHASH(sp->Session_ID);

	mtx_lock(&privp->sesshash[hash].mtx);
	LIST_INSERT_HEAD(&privp->sesshash[hash].head, sp, sessions);
	mtx_unlock(&privp->sesshash[hash].mtx);
}