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
struct TYPE_2__ {size_t len; int /*<<< orphan*/ * buf; } ;
struct window {TYPE_1__ out; } ;

/* Variables and functions */
 int error (char*) ; 
 scalar_t__ parse_int (char const**,size_t*,char const*) ; 
 int /*<<< orphan*/  strbuf_addch (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copyfrom_target(struct window *ctx, const char **instructions,
			   size_t nbytes, const char *instructions_end)
{
	size_t offset;
	if (parse_int(instructions, &offset, instructions_end))
		return -1;
	if (offset >= ctx->out.len)
		return error("invalid delta: copies from the future");
	for (; nbytes > 0; nbytes--)
		strbuf_addch(&ctx->out, ctx->out.buf[offset++]);
	return 0;
}