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
typedef  int uint16_t ;
struct TYPE_6__ {int score; int te; int qe; int score2; int te2; } ;
typedef  TYPE_1__ kswr_t ;
struct TYPE_7__ {int slen; int max; int /*<<< orphan*/ * qp; int /*<<< orphan*/ * Hmax; int /*<<< orphan*/ * E; int /*<<< orphan*/ * H1; int /*<<< orphan*/ * H0; } ;
typedef  TYPE_2__ kswq_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  __m128i ;

/* Variables and functions */
 int KSW_XSTOP ; 
 int KSW_XSUBO ; 
 scalar_t__ LIKELY (int) ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  __max_8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_adds_epi16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_cmpgt_epi16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_load_si128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mm_max_epi16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_movemask_epi8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_epi16 (int) ; 
 int /*<<< orphan*/  _mm_set1_epi32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_slli_si128 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _mm_store_si128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_subs_epu16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 TYPE_1__ g_defr ; 
 scalar_t__ realloc (int*,int) ; 

kswr_t ksw_i16(kswq_t *q, int tlen, const uint8_t *target, int _gapo, int _gape, int xtra) // the first gap costs -(_o+_e)
{
	int slen, i, m_b, n_b, te = -1, gmax = 0, minsc, endsc;
	uint64_t *b;
	__m128i zero, gapoe, gape, *H0, *H1, *E, *Hmax;
	kswr_t r;

#define __max_8(ret, xx) do { \
		(xx) = _mm_max_epi16((xx), _mm_srli_si128((xx), 8)); \
		(xx) = _mm_max_epi16((xx), _mm_srli_si128((xx), 4)); \
		(xx) = _mm_max_epi16((xx), _mm_srli_si128((xx), 2)); \
    	(ret) = _mm_extract_epi16((xx), 0); \
	} while (0)

	// initialization
	r = g_defr;
	minsc = (xtra&KSW_XSUBO)? xtra&0xffff : 0x10000;
	endsc = (xtra&KSW_XSTOP)? xtra&0xffff : 0x10000;
	m_b = n_b = 0; b = 0;
	zero = _mm_set1_epi32(0);
	gapoe = _mm_set1_epi16(_gapo + _gape);
	gape = _mm_set1_epi16(_gape);
	H0 = q->H0; H1 = q->H1; E = q->E; Hmax = q->Hmax;
	slen = q->slen;
	for (i = 0; i < slen; ++i) {
		_mm_store_si128(E + i, zero);
		_mm_store_si128(H0 + i, zero);
		_mm_store_si128(Hmax + i, zero);
	}
	// the core loop
	for (i = 0; i < tlen; ++i) {
		int j, k, imax;
		__m128i e, h, f = zero, max = zero, *S = q->qp + target[i] * slen; // s is the 1st score vector
		h = _mm_load_si128(H0 + slen - 1); // h={2,5,8,11,14,17,-1,-1} in the above example
		h = _mm_slli_si128(h, 2);
		for (j = 0; LIKELY(j < slen); ++j) {
			h = _mm_adds_epi16(h, *S++);
			e = _mm_load_si128(E + j);
			h = _mm_max_epi16(h, e);
			h = _mm_max_epi16(h, f);
			max = _mm_max_epi16(max, h);
			_mm_store_si128(H1 + j, h);
			h = _mm_subs_epu16(h, gapoe);
			e = _mm_subs_epu16(e, gape);
			e = _mm_max_epi16(e, h);
			_mm_store_si128(E + j, e);
			f = _mm_subs_epu16(f, gape);
			f = _mm_max_epi16(f, h);
			h = _mm_load_si128(H0 + j);
		}
		for (k = 0; LIKELY(k < 16); ++k) {
			f = _mm_slli_si128(f, 2);
			for (j = 0; LIKELY(j < slen); ++j) {
				h = _mm_load_si128(H1 + j);
				h = _mm_max_epi16(h, f);
				_mm_store_si128(H1 + j, h);
				h = _mm_subs_epu16(h, gapoe);
				f = _mm_subs_epu16(f, gape);
				if(UNLIKELY(!_mm_movemask_epi8(_mm_cmpgt_epi16(f, h)))) goto end_loop8;
			}
		}
end_loop8:
		__max_8(imax, max);
		if (imax >= minsc) {
			if (n_b == 0 || (int32_t)b[n_b-1] + 1 != i) {
				if (n_b == m_b) {
					m_b = m_b? m_b<<1 : 8;
					b = (uint64_t*)realloc(b, 8 * m_b);
				}
				b[n_b++] = (uint64_t)imax<<32 | i;
			} else if ((int)(b[n_b-1]>>32) < imax) b[n_b-1] = (uint64_t)imax<<32 | i; // modify the last
		}
		if (imax > gmax) {
			gmax = imax; te = i;
			for (j = 0; LIKELY(j < slen); ++j)
				_mm_store_si128(Hmax + j, _mm_load_si128(H1 + j));
			if (gmax >= endsc) break;
		}
		S = H1; H1 = H0; H0 = S;
	}
	r.score = gmax; r.te = te;
	{
		int max = -1, low, high, qlen = slen * 8;
		uint16_t *t = (uint16_t*)Hmax;
		for (i = 0, r.qe = -1; i < qlen; ++i, ++t)
			if ((int)*t > max) max = *t, r.qe = i / 8 + i % 8 * slen;
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