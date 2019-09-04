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
 int /*<<< orphan*/  line_terminator ; 
 int /*<<< orphan*/ * prefix ; 
 scalar_t__ prefix_len ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_name_quoted_relative (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_name(const char *name)
{
	/*
	 * With "--full-name", prefix_len=0; this caller needs to pass
	 * an empty string in that case (a NULL is good for "").
	 */
	write_name_quoted_relative(name, prefix_len ? prefix : NULL,
				   stdout, line_terminator);
}