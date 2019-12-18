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

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

char *
itoa7(int val)
{
    static char buffer[16];	/* result is built here */
    				/* 16 is sufficient since the largest number
				   we will ever convert will be 2^32-1,
				   which is 10 digits. */

	sprintf(buffer, "%6u", val);
    return (buffer);
}