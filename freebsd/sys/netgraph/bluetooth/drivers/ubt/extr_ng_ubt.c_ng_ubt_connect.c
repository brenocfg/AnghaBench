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
struct ubt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_FORCE_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_PEER (int /*<<< orphan*/ ) ; 
 struct ubt_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UBT_FLAG_T_START_ALL ; 
 int /*<<< orphan*/  UBT_NG_LOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_NG_UNLOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  ubt_task_schedule (struct ubt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ubt_connect(hook_p hook)
{
	struct ubt_softc	*sc = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));

	NG_HOOK_FORCE_QUEUE(NG_HOOK_PEER(hook));

	UBT_NG_LOCK(sc);
	ubt_task_schedule(sc, UBT_FLAG_T_START_ALL);
	UBT_NG_UNLOCK(sc);

	return (0);
}