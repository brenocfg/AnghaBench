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
typedef  int /*<<< orphan*/  u8 ;
struct sha1_state {unsigned int count; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 unsigned int SHA1_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  octeon_sha1_transform (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void __octeon_sha1_update(struct sha1_state *sctx, const u8 *data,
				 unsigned int len)
{
	unsigned int partial;
	unsigned int done;
	const u8 *src;

	partial = sctx->count % SHA1_BLOCK_SIZE;
	sctx->count += len;
	done = 0;
	src = data;

	if ((partial + len) >= SHA1_BLOCK_SIZE) {
		if (partial) {
			done = -partial;
			memcpy(sctx->buffer + partial, data,
			       done + SHA1_BLOCK_SIZE);
			src = sctx->buffer;
		}

		do {
			octeon_sha1_transform(src);
			done += SHA1_BLOCK_SIZE;
			src = data + done;
		} while (done + SHA1_BLOCK_SIZE <= len);

		partial = 0;
	}
	memcpy(sctx->buffer + partial, src, len - done);
}