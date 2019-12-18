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
 int /*<<< orphan*/  add_type (int,char*) ; 

void
c_initialize(void)
{

	/* add all the starting basic types */
	add_type(1, "int");
	add_type(1, "long");
	add_type(1, "short");
	add_type(1, "bool");
	add_type(1, "u_int");
	add_type(1, "u_long");
	add_type(1, "u_short");

}