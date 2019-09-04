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
struct strbuf {size_t len; } ;
struct line_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_read_binary (struct line_buffer*,struct strbuf*,size_t) ; 
 int input_error (struct line_buffer*) ; 

__attribute__((used)) static int read_to_fill_or_whine(struct line_buffer *file,
				struct strbuf *buf, size_t width)
{
	buffer_read_binary(file, buf, width - buf->len);
	if (buf->len != width)
		return input_error(file);
	return 0;
}