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
struct sha512_state {int curlen; unsigned long length; unsigned char* buf; } ;

/* Variables and functions */
 unsigned long MIN (unsigned long,unsigned long) ; 
 unsigned long SHA512_BLOCK_SIZE ; 
 int /*<<< orphan*/  os_memcpy (unsigned char*,unsigned char const*,unsigned long) ; 
 scalar_t__ sha512_compress (struct sha512_state*,unsigned char*) ; 

int sha512_process(struct sha512_state *md, const unsigned char *in,
		   unsigned long inlen)
{
	unsigned long n;

	if (md->curlen >= sizeof(md->buf))
		return -1;

	while (inlen > 0) {
		if (md->curlen == 0 && inlen >= SHA512_BLOCK_SIZE) {
			if (sha512_compress(md, (unsigned char *) in) < 0)
				return -1;
			md->length += SHA512_BLOCK_SIZE * 8;
			in += SHA512_BLOCK_SIZE;
			inlen -= SHA512_BLOCK_SIZE;
		} else {
			n = MIN(inlen, (SHA512_BLOCK_SIZE - md->curlen));
			os_memcpy(md->buf + md->curlen, in, n);
			md->curlen += n;
			in += n;
			inlen -= n;
			if (md->curlen == SHA512_BLOCK_SIZE) {
				if (sha512_compress(md, md->buf) < 0)
					return -1;
				md->length += 8 * SHA512_BLOCK_SIZE;
				md->curlen = 0;
			}
		}
	}

	return 0;
}