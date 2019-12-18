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
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 scalar_t__ continuation ; 

__attribute__((used)) static char *
prompt(EditLine *el)
{
	static char a[] = "\1\033[7m\1Edit$\1\033[0m\1 ";
	static char b[] = "Edit> ";

	return (continuation ? b : a);
}