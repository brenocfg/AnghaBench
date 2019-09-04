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
typedef  int /*<<< orphan*/  gameState_t ;
struct TYPE_2__ {int /*<<< orphan*/  gameState; } ;

/* Variables and functions */
 TYPE_1__ cl ; 

void CL_GetGameState( gameState_t *gs ) {
	*gs = cl.gameState;
}