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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {scalar_t__ result; int fd; } ;
typedef  TYPE_1__ isc_keyboard_t ;

/* Variables and functions */
 scalar_t__ ISC_R_CANCELED ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (unsigned int) ; 

isc_result_t
isc_keyboard_close(isc_keyboard_t *keyboard, unsigned int sleeptime) {
	REQUIRE(keyboard != NULL);

	if (sleeptime > 0 && keyboard->result != ISC_R_CANCELED)
		(void)Sleep(sleeptime*1000);

	keyboard->fd = -1;

	return (ISC_R_SUCCESS);
}