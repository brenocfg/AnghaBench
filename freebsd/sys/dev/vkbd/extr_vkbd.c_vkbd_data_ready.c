#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cc; } ;
struct TYPE_6__ {TYPE_1__ ks_inq; } ;
typedef  TYPE_2__ vkbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  VKBD_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vkbd_data_ready(vkbd_state_t *state)
{
	VKBD_LOCK_ASSERT(state, MA_OWNED);

	return (state->ks_inq.cc > 0);
}