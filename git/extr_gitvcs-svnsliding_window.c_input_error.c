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
 int /*<<< orphan*/  buffer_ferror (struct line_buffer*) ; 
 int error (char*) ; 
 int error_errno (char*) ; 

__attribute__((used)) static int input_error(struct line_buffer *file)
{
	if (!buffer_ferror(file))
		return error("delta preimage ends early");
	return error_errno("cannot read delta preimage");
}