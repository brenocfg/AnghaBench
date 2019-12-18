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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int LONG ; 
 int SHORT ; 
 int _mm_crc32_u32 (int,int const) ; 
 int _mm_crc32_u64 (int,int /*<<< orphan*/  const) ; 
 int _mm_crc32_u8 (int,unsigned char const) ; 
 int /*<<< orphan*/  crc32c_2long ; 
 int /*<<< orphan*/  crc32c_2short ; 
 int /*<<< orphan*/  crc32c_long ; 
 int crc32c_shift (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crc32c_short ; 

uint32_t
sse42_crc32c(uint32_t crc, const unsigned char *buf, unsigned len)
{
#ifdef __amd64__
	const size_t align = 8;
#else
	const size_t align = 4;
#endif
	const unsigned char *next, *end;
#ifdef __amd64__
	uint64_t crc0, crc1, crc2;
#else
	uint32_t crc0, crc1, crc2;
#endif

	next = buf;
	crc0 = crc;

	/* Compute the crc to bring the data pointer to an aligned boundary. */
	while (len && ((uintptr_t)next & (align - 1)) != 0) {
		crc0 = _mm_crc32_u8(crc0, *next);
		next++;
		len--;
	}

#if LONG > SHORT
	/*
	 * Compute the crc on sets of LONG*3 bytes, executing three independent
	 * crc instructions, each on LONG bytes -- this is optimized for the
	 * Nehalem, Westmere, Sandy Bridge, and Ivy Bridge architectures, which
	 * have a throughput of one crc per cycle, but a latency of three
	 * cycles.
	 */
	crc = 0;
	while (len >= LONG * 3) {
		crc1 = 0;
		crc2 = 0;
		end = next + LONG;
		do {
#ifdef __amd64__
			crc0 = _mm_crc32_u64(crc0, *(const uint64_t *)next);
			crc1 = _mm_crc32_u64(crc1,
			    *(const uint64_t *)(next + LONG));
			crc2 = _mm_crc32_u64(crc2,
			    *(const uint64_t *)(next + (LONG * 2)));
#else
			crc0 = _mm_crc32_u32(crc0, *(const uint32_t *)next);
			crc1 = _mm_crc32_u32(crc1,
			    *(const uint32_t *)(next + LONG));
			crc2 = _mm_crc32_u32(crc2,
			    *(const uint32_t *)(next + (LONG * 2)));
#endif
			next += align;
		} while (next < end);
		/*-
		 * Update the crc.  Try to do it in parallel with the inner
		 * loop.  'crc' is used to accumulate crc0 and crc1
		 * produced by the inner loop so that the next iteration
		 * of the loop doesn't depend on anything except crc2.
		 *
		 * The full expression for the update is:
		 *     crc = S*S*S*crc + S*S*crc0 + S*crc1
		 * where the terms are polynomials modulo the CRC polynomial.
		 * We regroup this subtly as:
		 *     crc = S*S * (S*crc + crc0) + S*crc1.
		 * This has an extra dependency which reduces possible
		 * parallelism for the expression, but it turns out to be
		 * best to intentionally delay evaluation of this expression
		 * so that it competes less with the inner loop.
		 *
		 * We also intentionally reduce parallelism by feedng back
		 * crc2 to the inner loop as crc0 instead of accumulating
		 * it in crc.  This synchronizes the loop with crc update.
		 * CPU and/or compiler schedulers produced bad order without
		 * this.
		 *
		 * Shifts take about 12 cycles each, so 3 here with 2
		 * parallelizable take about 24 cycles and the crc update
		 * takes slightly longer.  8 dependent crc32 instructions
		 * can run in 24 cycles, so the 3-way blocking is worse
		 * than useless for sizes less than 8 * <word size> = 64
		 * on amd64.  In practice, SHORT = 32 confirms these
		 * timing calculations by giving a small improvement
		 * starting at size 96.  Then the inner loop takes about
		 * 12 cycles and the crc update about 24, but these are
		 * partly in parallel so the total time is less than the
		 * 36 cycles that 12 dependent crc32 instructions would
		 * take.
		 *
		 * To have a chance of completely hiding the overhead for
		 * the crc update, the inner loop must take considerably
		 * longer than 24 cycles.  LONG = 64 makes the inner loop
		 * take about 24 cycles, so is not quite large enough.
		 * LONG = 128 works OK.  Unhideable overheads are about
		 * 12 cycles per inner loop.  All assuming timing like
		 * Haswell.
		 */
		crc = crc32c_shift(crc32c_long, crc) ^ crc0;
		crc1 = crc32c_shift(crc32c_long, crc1);
		crc = crc32c_shift(crc32c_2long, crc) ^ crc1;
		crc0 = crc2;
		next += LONG * 2;
		len -= LONG * 3;
	}
	crc0 ^= crc;
#endif /* LONG > SHORT */

	/*
	 * Do the same thing, but now on SHORT*3 blocks for the remaining data
	 * less than a LONG*3 block
	 */
	crc = 0;
	while (len >= SHORT * 3) {
		crc1 = 0;
		crc2 = 0;
		end = next + SHORT;
		do {
#ifdef __amd64__
			crc0 = _mm_crc32_u64(crc0, *(const uint64_t *)next);
			crc1 = _mm_crc32_u64(crc1,
			    *(const uint64_t *)(next + SHORT));
			crc2 = _mm_crc32_u64(crc2,
			    *(const uint64_t *)(next + (SHORT * 2)));
#else
			crc0 = _mm_crc32_u32(crc0, *(const uint32_t *)next);
			crc1 = _mm_crc32_u32(crc1,
			    *(const uint32_t *)(next + SHORT));
			crc2 = _mm_crc32_u32(crc2,
			    *(const uint32_t *)(next + (SHORT * 2)));
#endif
			next += align;
		} while (next < end);
		crc = crc32c_shift(crc32c_short, crc) ^ crc0;
		crc1 = crc32c_shift(crc32c_short, crc1);
		crc = crc32c_shift(crc32c_2short, crc) ^ crc1;
		crc0 = crc2;
		next += SHORT * 2;
		len -= SHORT * 3;
	}
	crc0 ^= crc;

	/* Compute the crc on the remaining bytes at native word size. */
	end = next + (len - (len & (align - 1)));
	while (next < end) {
#ifdef __amd64__
		crc0 = _mm_crc32_u64(crc0, *(const uint64_t *)next);
#else
		crc0 = _mm_crc32_u32(crc0, *(const uint32_t *)next);
#endif
		next += align;
	}
	len &= (align - 1);

	/* Compute the crc for any trailing bytes. */
	while (len) {
		crc0 = _mm_crc32_u8(crc0, *next);
		next++;
		len--;
	}

	return ((uint32_t)crc0);
}