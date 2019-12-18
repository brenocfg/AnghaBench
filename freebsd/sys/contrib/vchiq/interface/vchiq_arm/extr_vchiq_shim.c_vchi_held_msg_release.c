#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {scalar_t__ message; scalar_t__ service; } ;
typedef  TYPE_1__ VCHI_HELD_MSG_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHIQ_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int32_t vchi_held_msg_release(VCHI_HELD_MSG_T *message)
{
	vchiq_release_message((VCHIQ_SERVICE_HANDLE_T)message->service,
		(VCHIQ_HEADER_T *)message->message);

	return 0;
}