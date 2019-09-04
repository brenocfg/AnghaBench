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
 scalar_t__ buffer_ferror (struct line_buffer*) ; 
 int error (char*) ; 
 int error_errno (char*) ; 

__attribute__((used)) static int error_short_read(struct line_buffer *input)
{
	if (buffer_ferror(input))
		return error_errno("error reading delta");
	return error("invalid delta: unexpected end of file");
}