#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cc; TYPE_3__* ah; } ;
typedef  TYPE_1__ uiArea ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {TYPE_1__* a; } ;
typedef  TYPE_2__ areaWidget ;
struct TYPE_8__ {int /*<<< orphan*/  (* MouseCrossed ) (TYPE_3__*,TYPE_1__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_EVENT_PROPAGATE ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  uiprivClickCounterReset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean onCrossing(areaWidget *aw, int left)
{
	uiArea *a = aw->a;

	(*(a->ah->MouseCrossed))(a->ah, a, left);
	uiprivClickCounterReset(a->cc);
	return GDK_EVENT_PROPAGATE;
}