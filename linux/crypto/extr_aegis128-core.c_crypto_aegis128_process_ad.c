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
union aegis_block {scalar_t__ bytes; } ;
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;
struct scatter_walk {int dummy; } ;
struct aegis_state {int dummy; } ;

/* Variables and functions */
 unsigned int AEGIS_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_aegis128_ad (struct aegis_state*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_aegis128_update_a (struct aegis_state*,union aegis_block*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,unsigned int) ; 
 unsigned int scatterwalk_clamp (struct scatter_walk*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int /*<<< orphan*/ ,unsigned int) ; 
 void* scatterwalk_map (struct scatter_walk*) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 
 int /*<<< orphan*/  scatterwalk_unmap (void*) ; 

__attribute__((used)) static void crypto_aegis128_process_ad(struct aegis_state *state,
				       struct scatterlist *sg_src,
				       unsigned int assoclen)
{
	struct scatter_walk walk;
	union aegis_block buf;
	unsigned int pos = 0;

	scatterwalk_start(&walk, sg_src);
	while (assoclen != 0) {
		unsigned int size = scatterwalk_clamp(&walk, assoclen);
		unsigned int left = size;
		void *mapped = scatterwalk_map(&walk);
		const u8 *src = (const u8 *)mapped;

		if (pos + size >= AEGIS_BLOCK_SIZE) {
			if (pos > 0) {
				unsigned int fill = AEGIS_BLOCK_SIZE - pos;
				memcpy(buf.bytes + pos, src, fill);
				crypto_aegis128_update_a(state, &buf);
				pos = 0;
				left -= fill;
				src += fill;
			}

			crypto_aegis128_ad(state, src, left);
			src += left & ~(AEGIS_BLOCK_SIZE - 1);
			left &= AEGIS_BLOCK_SIZE - 1;
		}

		memcpy(buf.bytes + pos, src, left);

		pos += left;
		assoclen -= size;
		scatterwalk_unmap(mapped);
		scatterwalk_advance(&walk, size);
		scatterwalk_done(&walk, 0, assoclen);
	}

	if (pos > 0) {
		memset(buf.bytes + pos, 0, AEGIS_BLOCK_SIZE - pos);
		crypto_aegis128_update_a(state, &buf);
	}
}