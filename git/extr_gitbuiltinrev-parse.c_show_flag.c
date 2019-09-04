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
 int DO_FLAGS ; 
 int DO_NOREV ; 
 int DO_REVS ; 
 int filter ; 
 scalar_t__ is_rev_argument (char const*) ; 
 int /*<<< orphan*/  show (char const*) ; 

__attribute__((used)) static int show_flag(const char *arg)
{
	if (!(filter & DO_FLAGS))
		return 0;
	if (filter & (is_rev_argument(arg) ? DO_REVS : DO_NOREV)) {
		show(arg);
		return 1;
	}
	return 0;
}