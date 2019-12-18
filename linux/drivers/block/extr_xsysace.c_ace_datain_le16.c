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
typedef  int /*<<< orphan*/  u16 ;
struct ace_device {int /*<<< orphan*/ * data_ptr; scalar_t__ baseaddr; } ;

/* Variables and functions */
 int ACE_FIFO_SIZE ; 
 int /*<<< orphan*/  in_be16 (scalar_t__) ; 

__attribute__((used)) static void ace_datain_le16(struct ace_device *ace)
{
	int i = ACE_FIFO_SIZE / 2;
	u16 *dst = ace->data_ptr;
	while (i--)
		*dst++ = in_be16(ace->baseaddr + 0x40);
	ace->data_ptr = dst;
}