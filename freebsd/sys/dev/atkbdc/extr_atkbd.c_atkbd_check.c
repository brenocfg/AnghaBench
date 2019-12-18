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
struct TYPE_5__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_6__ {int /*<<< orphan*/  kbdc; } ;
typedef  TYPE_2__ atkbd_state_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_1__*) ; 
 int kbdc_data_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbd_check(keyboard_t *kbd)
{
	if (!KBD_IS_ACTIVE(kbd))
		return FALSE;
	return kbdc_data_ready(((atkbd_state_t *)kbd->kb_data)->kbdc);
}