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
typedef  int u8 ;
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct wp512_ctx {int bufferBits; int* buffer; int* bitLength; int bufferPos; } ;
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int WP512_BLOCK_SIZE ; 
 struct wp512_ctx* shash_desc_ctx (struct shash_desc*) ; 
 int /*<<< orphan*/  wp512_process_buffer (struct wp512_ctx*) ; 

__attribute__((used)) static int wp512_update(struct shash_desc *desc, const u8 *source,
			 unsigned int len)
{
	struct wp512_ctx *wctx = shash_desc_ctx(desc);
	int sourcePos    = 0;
	unsigned int bits_len = len * 8; // convert to number of bits
	int sourceGap    = (8 - ((int)bits_len & 7)) & 7;
	int bufferRem    = wctx->bufferBits & 7;
	int i;
	u32 b, carry;
	u8 *buffer       = wctx->buffer;
	u8 *bitLength    = wctx->bitLength;
	int bufferBits   = wctx->bufferBits;
	int bufferPos    = wctx->bufferPos;

	u64 value = bits_len;
	for (i = 31, carry = 0; i >= 0 && (carry != 0 || value != 0ULL); i--) {
		carry += bitLength[i] + ((u32)value & 0xff);
		bitLength[i] = (u8)carry;
		carry >>= 8;
		value >>= 8;
	}
	while (bits_len > 8) {
		b = ((source[sourcePos] << sourceGap) & 0xff) |
		((source[sourcePos + 1] & 0xff) >> (8 - sourceGap));
		buffer[bufferPos++] |= (u8)(b >> bufferRem);
		bufferBits += 8 - bufferRem;
		if (bufferBits == WP512_BLOCK_SIZE * 8) {
			wp512_process_buffer(wctx);
			bufferBits = bufferPos = 0;
		}
		buffer[bufferPos] = b << (8 - bufferRem);
		bufferBits += bufferRem;
		bits_len -= 8;
		sourcePos++;
	}
	if (bits_len > 0) {
		b = (source[sourcePos] << sourceGap) & 0xff;
		buffer[bufferPos] |= b >> bufferRem;
	} else {
		b = 0;
	}
	if (bufferRem + bits_len < 8) {
		bufferBits += bits_len;
	} else {
		bufferPos++;
		bufferBits += 8 - bufferRem;
		bits_len -= 8 - bufferRem;
		if (bufferBits == WP512_BLOCK_SIZE * 8) {
			wp512_process_buffer(wctx);
			bufferBits = bufferPos = 0;
		}
		buffer[bufferPos] = b << (8 - bufferRem);
		bufferBits += (int)bits_len;
	}

	wctx->bufferBits   = bufferBits;
	wctx->bufferPos    = bufferPos;

	return 0;
}