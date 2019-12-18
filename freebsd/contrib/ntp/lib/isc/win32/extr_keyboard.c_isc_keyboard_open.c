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
struct TYPE_3__ {int fd; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ isc_keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_IOERROR ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int _fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 

isc_result_t
isc_keyboard_open(isc_keyboard_t *keyboard) {
	int fd;

	REQUIRE(keyboard != NULL);

	fd = _fileno(stdin);
	if (fd < 0)
		return (ISC_R_IOERROR);

	keyboard->fd = fd;

	keyboard->result = ISC_R_SUCCESS;

	return (ISC_R_SUCCESS);
}