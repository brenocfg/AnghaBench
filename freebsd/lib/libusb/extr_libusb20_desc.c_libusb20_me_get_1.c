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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct libusb20_me_struct {scalar_t__ len; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ LIBUSB20_ADD_BYTES (int /*<<< orphan*/ ,scalar_t__) ; 

uint8_t
libusb20_me_get_1(const struct libusb20_me_struct *ie, uint16_t offset)
{
	if (offset < ie->len) {
		return (*((uint8_t *)LIBUSB20_ADD_BYTES(ie->ptr, offset)));
	}
	return (0);
}