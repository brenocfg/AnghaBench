#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pendingLegsAnim; } ;
typedef  TYPE_1__ playerInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  UI_ForceLegsAnim (TYPE_1__*,int) ; 

__attribute__((used)) static void UI_SetLegsAnim( playerInfo_t *pi, int anim ) {
	if ( pi->pendingLegsAnim ) {
		anim = pi->pendingLegsAnim;
		pi->pendingLegsAnim = 0;
	}
	UI_ForceLegsAnim( pi, anim );
}