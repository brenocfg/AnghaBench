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
 int /*<<< orphan*/  addchar (char) ; 
 char* buffer ; 
 scalar_t__ current ; 

__attribute__((used)) static char *
getstring(void)
{
	addchar('\0');
	current = 0;
	return buffer;
}