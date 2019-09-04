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
struct line_buffer {scalar_t__ infile; } ;

/* Variables and functions */
 int fclose (scalar_t__) ; 
 int ferror (scalar_t__) ; 
 scalar_t__ stdin ; 

int buffer_deinit(struct line_buffer *buf)
{
	int err;
	if (buf->infile == stdin)
		return ferror(buf->infile);
	err = ferror(buf->infile);
	err |= fclose(buf->infile);
	return err;
}