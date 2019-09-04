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
struct strbuf {int dummy; } ;
struct line_buffer {int /*<<< orphan*/  infile; } ;

/* Variables and functions */
 size_t strbuf_fread (struct strbuf*,size_t,int /*<<< orphan*/ ) ; 

size_t buffer_read_binary(struct line_buffer *buf,
				struct strbuf *sb, size_t size)
{
	return strbuf_fread(sb, size, buf->infile);
}