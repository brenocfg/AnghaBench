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
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  set_type (char*) ; 

void
setbinary(int argc, char *argv[])
{

	if (argc == 0) {
		UPRINTF("usage: %s\n", argv[0]);
		code = -1;
		return;
	}
	set_type("binary");
}