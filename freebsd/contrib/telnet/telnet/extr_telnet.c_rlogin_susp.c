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
 int bol ; 
 int /*<<< orphan*/  command (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ local ; 

int
rlogin_susp(void)
{
    if (local) {
	local = 0;
	bol = 1;
	command(0, "z\n", 2);
	return(1);
    }
    return(0);
}