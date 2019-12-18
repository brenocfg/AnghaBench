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
typedef  int /*<<< orphan*/  UInt32 ;

/* Variables and functions */
 unsigned char read_byte (int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ unsigned char get_byte(void)
{
	unsigned char *buffer;
	UInt32 fake;
	
	return read_byte(0, &buffer, &fake), *buffer;
}