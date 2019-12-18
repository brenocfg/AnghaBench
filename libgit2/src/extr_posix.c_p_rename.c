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
 int /*<<< orphan*/  link (char const*,char const*) ; 
 int /*<<< orphan*/  p_unlink (char const*) ; 
 int /*<<< orphan*/  rename (char const*,char const*) ; 

int p_rename(const char *from, const char *to)
{
	if (!link(from, to)) {
		p_unlink(from);
		return 0;
	}

	if (!rename(from, to))
		return 0;

	return -1;
}