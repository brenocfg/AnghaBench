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
 int clear_eol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msglen ; 
 int /*<<< orphan*/  putchar (char) ; 

void
clear_message(void)
{
    if (clear_eol(msglen) == 1)
    {
	putchar('\r');
    }
}