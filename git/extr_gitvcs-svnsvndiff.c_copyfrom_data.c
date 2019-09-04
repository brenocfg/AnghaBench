#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t const len; scalar_t__ buf; } ;
struct window {TYPE_1__ data; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int error (char*) ; 
 int /*<<< orphan*/  strbuf_add (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 scalar_t__ unsigned_add_overflows (size_t const,size_t) ; 

__attribute__((used)) static int copyfrom_data(struct window *ctx, size_t *data_pos, size_t nbytes)
{
	const size_t pos = *data_pos;
	if (unsigned_add_overflows(pos, nbytes) ||
	    pos + nbytes > ctx->data.len)
		return error("invalid delta: copies unavailable inline data");
	strbuf_add(&ctx->out, ctx->data.buf + pos, nbytes);
	*data_pos += nbytes;
	return 0;
}