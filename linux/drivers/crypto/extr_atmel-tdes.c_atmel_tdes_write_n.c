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
typedef  int u32 ;
struct atmel_tdes_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_tdes_write (struct atmel_tdes_dev*,int,int) ; 

__attribute__((used)) static void atmel_tdes_write_n(struct atmel_tdes_dev *dd, u32 offset,
					u32 *value, int count)
{
	for (; count--; value++, offset += 4)
		atmel_tdes_write(dd, offset, *value);
}