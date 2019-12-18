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
typedef  int uint8_t ;

/* Variables and functions */
 int host_read (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
hostcons_getchar()
{
	uint8_t ch;
	int rv;

	rv = host_read(0, &ch, 1);
	if (rv == 1)
		return (ch);
	return (-1);
}