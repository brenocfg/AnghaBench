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
typedef  int uint16_t ;
struct libusb20_me_struct {int dummy; } ;

/* Variables and functions */
 int libusb20_me_get_1 (struct libusb20_me_struct const*,int) ; 

uint16_t
libusb20_me_get_2(const struct libusb20_me_struct *ie, uint16_t offset)
{
	return (libusb20_me_get_1(ie, offset) |
	    (libusb20_me_get_1(ie, offset + 1) << 8));
}