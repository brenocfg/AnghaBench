#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_6__ {int score; int te; int qe; int score2; int te2; } ;
typedef  TYPE_1__ kswr_t ;
struct TYPE_7__ {int shift; int slen; int max; int /*<<< orphan*/ * qp; int /*<<< orphan*/ * Hmax; int /*<<< orphan*/ * E; int /*<<< orphan*/ * H1; int /*<<< orphan*/ * H0; } ;
typedef  TYPE_2__ kswq_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int KSW_XSTOP ; 
 int KSW_XSUBO ; 
 scalar_t__ LIKELY (int) ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  __max_16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_adds_epu8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_cmpeq_epi8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_load_si128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mm_max_epu8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _mm_movemask_epi8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_epi32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_epi8 (int) ; 
 int /*<<< orphan*/  _mm_slli_si128 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_store_si128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_subs_epu8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 TYPE_1__ g_defr ; 
 scalar_t__ realloc (int*,int) ; 

kswr_t ksw_u8(kswq_t *q, int tlen, const uint8_t *target, int _gapo, int _gape, int xtra) // the first gap costs -(_o+_e)
{
	int slen, i, m_b, n_b, te = -1, gmax = 0, minsc, endsc;
	uint64_t *b;
	__m128i zero, gapoe, gape, shift, *H0, *H1, *E, *Hmax;
	kswr_t r;

#define __max_16(ret, xx) do { \
		(xx) = _mm_max_epu8((xx), _mm_srli_si128((xx), 8)); \
		(xx) = _mm_max_epu8((xx), _mm_srli_si128((xx), 4)); \
		(xx) = _mm_max_epu8((xx), _mm_srli_si128((xx), 2)); \
		(xx) = _mm_max_epu8((xx), _mm_srli_si128((xx), 1)); \
    	(ret) = _mm_extract_epi16((xx), 0) & 0x00ff; \
	} while (0)

	// initialization
	r = g_defr;
	minsc = (xtra&KSW_XSUBO)? xtra&0xffff : 0x10000;
	endsc = (xtra&KSW_XSTOP)? xtra&0xffff : 0x10000;
	m_b = n_b = 0; b = 0;
	zero = _mm_set1_epi32(0);
	gapoe = _mm_set1_epi8(_gapo + _gape);
	gape = _mm_set1_epi8(_gape);
	shift = _mm_set1_epi8(q->shift);
	H0 = q->H0; H1 = q->H1; E = q->E; Hmax = q->Hmax;
	slen = q->slen;
	for (i = 0; i < slen; ++i) {
		_mm_store_si128(E + i, zero);
		_mm_store_si128(H0 + i, zero);
		_mm_store_si128(Hmax + i, zero);
	}
	// the core loop
	for (i = 0; i < tlen; ++i) {
		int j, k, cmp, imax;
		__m128i e, h, f = zero, max = zero, *S = q->qp + target[i] * slen; // s is the 1st score vector
		h = _mm_load_si128(H0 + slen - 1); // h={2,5,8,11,14,17,-1,-1} in the above example
		h = _mm_slli_si128(h, 1); // h=H(i-1,-1); << instead of >> because x64 is little-endian
		for (j = 0; LIKELY(j < slen); ++j) {
			/* SW cells are computed in the following order:
			 *   H(i,j)   = max{H(i-1,j-1)+S(i,j), E(i,j), F(i,j)}
			 *   E(i+1,j) = max{H(i,j)-q, E(i,j)-r}
			 *   F(i,j+1) = max{H(i,j)-q, F(i,j)-r}
			 */
			// compute H'(i,j); note that at the beginning, h=H'(i-1,j-1)
			h = _mm_adds_epu8(h, _mm_load_si128(S + j));
			h = _mm_subs_epu8(h, shift); // h=H'(i-1,j-1)+S(i,j)
			e = _mm_load_si128(E + j); // e=E'(i,j)
			h = _mm_max_epu8(h, e);
			h = _mm_max_epu8(h, f); // h=H'(i,j)
			max = _mm_max_epu8(max, h); // set max
			_mm_store_si128(H1 + j, h); // save to H'(i,j)
			// now compute E'(i+1,j)
			h = _mm_subs_epu8(h, gapoe); // h=H'(i,j)-gapo
			e = _mm_subs_epu8(e, gape); // e=E'(i,j)-gape
			e = _mm_max_epu8(e, h); // e=E'(i+1,j)
			_mm_store_si128(E + j, e); // save to E'(i+1,j)
			// now compute F'(i,j+1)
			f = _mm_subs_epu8(f, gape);
			f = _mm_max_epu8(f, h);
			// get H'(i-1,j) and prepare for the next j
			h = _mm_load_si128(H0 + j); // h=H'(i-1,j)
		}
		// NB: we do not need to set E(i,j) as we disallow adjecent insertion and then deletion
		for (k = 0; LIKELY(k < 16); ++k) { // this block mimics SWPS3; NB: H(i,j) updated in the lazy-F loop cannot exceed max
			f = _mm_slli_si128(f, 1);
			for (j = 0; LIKELY(j < slen); ++j) {
				h = _mm_load_si128(H1 + j);
				h = _mm_max_epu8(h, f); // h=H'(i,j)
				_mm_store_si128(H1 + j, h);
				h = _mm_subs_epu8(h, gapoe);
				f = _mm_subs_epu8(f, gape);
				cmp = _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_subs_epu8(f, h), zero));
				if (UNLIKELY(cmp == 0xffff)) goto end_loop16;
			}
		}
end_loop16:
		//int k;for (k=0;k<16;++k)printf("%d ", ((uint8_t*)&max)[k]);printf("\n");
		__max_16(imax, max); // imax is the maximum number in max
		if (imax >= minsc) { // write the b array; this condition adds branching unfornately
			if (n_b == 0 || (int32_t)b[n_b-1] + 1 != i) { // then append
				if (n_b == m_b) {
					m_b = m_b? m_b<<1 : 8;
					b = (uint64_t*)realloc(b, 8 * m_b);
				}
				b[n_b++] = (uint64_t)imax<<32 | i;
			} else if ((int)(b[n_b-1]>>32) < imax) b[n_b-1] = (uint64_t)imax<<32 | i; // modify the last
		}
		if (imax > gmax) {
			gmax = imax; te = i; // te is the end position on the target
			for (j = 0; LIKELY(j < slen); ++j) // keep the H1 vector
				_mm_store_si128(Hmax + j, _mm_load_si128(H1 + j));
			if (gmax + q->shift >= 255 || gmax >= endsc) break;
		}
		S = H1; H1 = H0; H0 = S; // swap H0 and H1
	}
	r.score = gmax + q->shift < 255? gmax : 255;
	r.te = te;
	if (r.score != 255) { // get a->qe, the end of query match; find the 2nd best score
		int max = -1, low, high, qlen = slen * 16;
		uint8_t *t = (uint8_t*)Hmax;
		for (i = 0; i < qlen; ++i, ++t)
			if ((int)*t > max) max = *t, r.qe = i / 16 + i % 16 * slen;
		//printf("%d,%d\n", max, gmax);
		if (b) {
			i = (r.score + q->max - 1) / q->max;
			low = te - i; high = te + i;
			for (i = 0; i < n_b; ++i) {
				int e = (int32_t)b[i];
				if ((e < low || e > high) && (int)(b[i]>>32) > r.score2)
					r.score2 = b[i]>>32, r.te2 = e;
			}
		}
	}
	free(b);
	return r;
}