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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ucl_emitter_functions {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* ucl_emitter_append_len ) (unsigned char*,unsigned int,int /*<<< orphan*/ ) ;} ;
struct ucl_emitter_context {struct ucl_emitter_functions* func; } ;
typedef  int /*<<< orphan*/  bl ;

/* Variables and functions */
 int /*<<< orphan*/  TO_BE16 (size_t) ; 
 int /*<<< orphan*/  TO_BE32 (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,unsigned int,int /*<<< orphan*/ ) ; 

void
ucl_emitter_print_object_msgpack (struct ucl_emitter_context *ctx, size_t len)
{
	const struct ucl_emitter_functions *func = ctx->func;
	const unsigned char fix_mask = 0x80, l16_ch = 0xde, l32_ch = 0xdf;
	unsigned char buf[5];
	unsigned blen;

	if (len <= 0xF) {
		blen = 1;
		buf[0] = (len | fix_mask) & 0xff;
	}
	else if (len <= 0xffff) {
		uint16_t bl = TO_BE16 (len);

		blen = 3;
		buf[0] = l16_ch;
		memcpy (&buf[1], &bl, sizeof (bl));
	}
	else {
		uint32_t bl = TO_BE32 (len);

		blen = 5;
		buf[0] = l32_ch;
		memcpy (&buf[1], &bl, sizeof (bl));
	}

	func->ucl_emitter_append_len (buf, blen, func->ud);
}