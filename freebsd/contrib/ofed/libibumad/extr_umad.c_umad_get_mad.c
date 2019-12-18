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
struct TYPE_2__ {int /*<<< orphan*/  pkey_index; } ;
struct ib_user_mad {void* data; TYPE_1__ addr; } ;

/* Variables and functions */
 scalar_t__ new_user_mad_api ; 

void *umad_get_mad(void *umad)
{
	return new_user_mad_api ? ((struct ib_user_mad *)umad)->data :
	    (void *)&((struct ib_user_mad *)umad)->addr.pkey_index;
}