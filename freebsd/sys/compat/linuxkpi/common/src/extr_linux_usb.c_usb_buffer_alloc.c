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
typedef  int /*<<< orphan*/  usb_size_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void   *
usb_buffer_alloc(struct usb_device *dev, usb_size_t size, uint16_t mem_flags, uint8_t *dma_addr)
{
	return (malloc(size, M_USBDEV, M_WAITOK | M_ZERO));
}