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
struct line_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  handle_command (char const*,char const*,struct line_buffer*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void handle_line(const char *line, struct line_buffer *stdin_buf)
{
	const char *arg = strchr(line, ' ');
	if (!arg)
		die("no argument in line: %s", line);
	handle_command(line, arg + 1, stdin_buf);
}