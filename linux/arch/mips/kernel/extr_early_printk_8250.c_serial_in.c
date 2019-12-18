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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  readb (scalar_t__) ; 
 scalar_t__ serial8250_base ; 
 int serial8250_reg_shift ; 

__attribute__((used)) static inline u8 serial_in(int offset)
{
	return readb(serial8250_base + (offset << serial8250_reg_shift));
}