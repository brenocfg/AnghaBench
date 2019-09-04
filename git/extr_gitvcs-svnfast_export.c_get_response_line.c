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
 scalar_t__ buffer_ferror (int /*<<< orphan*/ *) ; 
 char* buffer_read_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  report_buffer ; 

__attribute__((used)) static const char *get_response_line(void)
{
	const char *line = buffer_read_line(&report_buffer);
	if (line)
		return line;
	if (buffer_ferror(&report_buffer))
		die_errno("error reading from fast-import");
	die("unexpected end of fast-import feedback");
}