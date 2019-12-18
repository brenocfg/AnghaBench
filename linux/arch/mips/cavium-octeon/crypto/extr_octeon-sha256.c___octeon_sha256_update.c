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
struct sha256_state {unsigned int count; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 unsigned int SHA256_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  octeon_sha256_transform (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void __octeon_sha256_update(struct sha256_state *sctx, const u8 *data,
				   unsigned int len)
{
	unsigned int partial;
	unsigned int done;
	const u8 *src;

	partial = sctx->count % SHA256_BLOCK_SIZE;
	sctx->count += len;
	done = 0;
	src = data;

	if ((partial + len) >= SHA256_BLOCK_SIZE) {
		if (partial) {
			done = -partial;
			memcpy(sctx->buf + partial, data,
			       done + SHA256_BLOCK_SIZE);
			src = sctx->buf;
		}

		do {
			octeon_sha256_transform(src);
			done += SHA256_BLOCK_SIZE;
			src = data + done;
		} while (done + SHA256_BLOCK_SIZE <= len);

		partial = 0;
	}
	memcpy(sctx->buf + partial, src, len - done);
}