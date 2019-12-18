#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct window {TYPE_1__* in; int /*<<< orphan*/  out; } ;
struct TYPE_4__ {scalar_t__ buf; } ;
struct TYPE_3__ {size_t width; TYPE_2__ buf; } ;

/* Variables and functions */
 int error (char*) ; 
 scalar_t__ parse_int (char const**,size_t*,char const*) ; 
 int /*<<< orphan*/  strbuf_add (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 scalar_t__ unsigned_add_overflows (size_t,size_t) ; 

__attribute__((used)) static int copyfrom_source(struct window *ctx, const char **instructions,
			   size_t nbytes, const char *insns_end)
{
	size_t offset;
	if (parse_int(instructions, &offset, insns_end))
		return -1;
	if (unsigned_add_overflows(offset, nbytes) ||
	    offset + nbytes > ctx->in->width)
		return error("invalid delta: copies source data outside view");
	strbuf_add(&ctx->out, ctx->in->buf.buf + offset, nbytes);
	return 0;
}