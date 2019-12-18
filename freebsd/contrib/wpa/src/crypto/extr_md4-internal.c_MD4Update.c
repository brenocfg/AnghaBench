#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int count; unsigned char const* buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD4Transform (int /*<<< orphan*/ ,unsigned char const*) ; 
 int MD4_BLOCK_LENGTH ; 
 int /*<<< orphan*/  os_memcpy (unsigned char const*,unsigned char const*,size_t) ; 

__attribute__((used)) static void MD4Update(MD4_CTX *ctx, const unsigned char *input, size_t len)
{
	size_t have, need;

	/* Check how many bytes we already have and how many more we need. */
	have = (size_t)((ctx->count >> 3) & (MD4_BLOCK_LENGTH - 1));
	need = MD4_BLOCK_LENGTH - have;

	/* Update bitcount */
	ctx->count += (u64)len << 3;

	if (len >= need) {
		if (have != 0) {
			os_memcpy(ctx->buffer + have, input, need);
			MD4Transform(ctx->state, ctx->buffer);
			input += need;
			len -= need;
			have = 0;
		}

		/* Process data in MD4_BLOCK_LENGTH-byte chunks. */
		while (len >= MD4_BLOCK_LENGTH) {
			MD4Transform(ctx->state, input);
			input += MD4_BLOCK_LENGTH;
			len -= MD4_BLOCK_LENGTH;
		}
	}

	/* Handle any remaining bytes of data. */
	if (len != 0)
		os_memcpy(ctx->buffer + have, input, len);
}