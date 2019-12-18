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
 int /*<<< orphan*/  output_buffer ; 
 scalar_t__ output_buffer_length ; 
 scalar_t__ output_in_paragraph ; 
 int /*<<< orphan*/  output_indent (size_t) ; 
 scalar_t__ pending_spaces ; 
 int /*<<< orphan*/  wprintf (char*,int,int /*<<< orphan*/ ) ; 
 size_t x ; 
 scalar_t__ x0 ; 

__attribute__((used)) static void
new_paragraph(size_t old_indent, size_t indent)
{
	if (output_buffer_length) {
		if (old_indent > 0)
			output_indent(old_indent);
		wprintf(L"%.*ls\n", (int)output_buffer_length, output_buffer);
	}
	x = indent;
	x0 = 0;
	output_buffer_length = 0;
	pending_spaces = 0;
	output_in_paragraph = 0;
}