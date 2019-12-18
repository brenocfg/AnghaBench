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
typedef  scalar_t__ CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  L (char*) ; 
 scalar_t__ STRCHR (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
is_special(CHAR_T c)
{
	/*
	 * !!!
	 * `*' and `$' are ordinary when appear at the beginning of a RE,
	 * but it's safe to distinguish them from the ordinary characters.
	 * The tilde is vi-specific, of course.
	 */
	return (STRCHR(L(".[*\\^$~"), c) && c);
}