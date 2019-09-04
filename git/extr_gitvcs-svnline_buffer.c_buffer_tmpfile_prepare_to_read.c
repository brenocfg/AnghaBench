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
struct line_buffer {int /*<<< orphan*/  infile; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 long error_errno (char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ ) ; 

long buffer_tmpfile_prepare_to_read(struct line_buffer *buf)
{
	long pos = ftell(buf->infile);
	if (pos < 0)
		return error_errno("ftell error");
	if (fseek(buf->infile, 0, SEEK_SET))
		return error_errno("seek error");
	return pos;
}