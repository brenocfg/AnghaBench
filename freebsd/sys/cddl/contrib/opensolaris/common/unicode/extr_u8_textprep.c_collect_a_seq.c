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
typedef  size_t uchar_t ;
typedef  scalar_t__ u8_normalization_states_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 size_t U8_ASCII_TOLOWER (size_t) ; 
 size_t U8_ASCII_TOUPPER (size_t) ; 
 size_t U8_COMBINING_CLASS_STARTER ; 
 scalar_t__ U8_HANGUL_COMPOSABLE_LV_T (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ U8_HANGUL_COMPOSABLE_L_V (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t U8_HANGUL_JAMO_1ST_BYTE ; 
 int U8_MAX_CHARS_A_SEQ ; 
 int U8_MB_CUR_MAX ; 
 int /*<<< orphan*/  U8_PUT_3BYTES_INTO_UTF32 (int /*<<< orphan*/ ,size_t,size_t,size_t) ; 
 scalar_t__ U8_STATE_COMBINING_MARK ; 
 scalar_t__ U8_STATE_HANGUL_LV ; 
 scalar_t__ U8_STATE_HANGUL_LVT ; 
 scalar_t__ U8_STATE_START ; 
 int /*<<< orphan*/  U8_STREAM_SAFE_TEXT_MAX ; 
 int /*<<< orphan*/  U8_SWAP_COMB_MARKS (size_t,size_t) ; 
 size_t U8_UPPER_LIMIT_IN_A_SEQ ; 
 size_t combining_class (size_t,size_t*,int) ; 
 size_t do_case_conv (size_t,size_t*,size_t*,int,scalar_t__) ; 
 int do_composition (size_t,size_t*,size_t*,size_t*,size_t*,size_t,size_t**,size_t*) ; 
 void* do_decomp (size_t,size_t*,size_t*,int,scalar_t__,scalar_t__*) ; 
 int* u8_number_of_bytes ; 

__attribute__((used)) static size_t
collect_a_seq(size_t uv, uchar_t *u8s, uchar_t **source, uchar_t *slast,
	boolean_t is_it_toupper,
	boolean_t is_it_tolower,
	boolean_t canonical_decomposition,
	boolean_t compatibility_decomposition,
	boolean_t canonical_composition,
	int *errnum, u8_normalization_states_t *state)
{
	uchar_t *s;
	int sz;
	int saved_sz;
	size_t i;
	size_t j;
	size_t k;
	size_t l;
	uchar_t comb_class[U8_MAX_CHARS_A_SEQ];
	uchar_t disp[U8_MAX_CHARS_A_SEQ];
	uchar_t start[U8_MAX_CHARS_A_SEQ];
	uchar_t u8t[U8_MB_CUR_MAX];
	uchar_t uts[U8_STREAM_SAFE_TEXT_MAX + 1];
	uchar_t tc;
	size_t last;
	size_t saved_last;
	uint32_t u1;

	/*
	 * Save the source string pointer which we will return a changed
	 * pointer if we do processing.
	 */
	s = *source;

	/*
	 * The following is a fallback for just in case callers are not
	 * checking the string boundaries before the calling.
	 */
	if (s >= slast) {
		u8s[0] = '\0';

		return (0);
	}

	/*
	 * As the first thing, let's collect a character and do case
	 * conversion if necessary.
	 */

	sz = u8_number_of_bytes[*s];

	if (sz < 0) {
		*errnum = EILSEQ;

		u8s[0] = *s++;
		u8s[1] = '\0';

		*source = s;

		return (1);
	}

	if (sz == 1) {
		if (is_it_toupper)
			u8s[0] = U8_ASCII_TOUPPER(*s);
		else if (is_it_tolower)
			u8s[0] = U8_ASCII_TOLOWER(*s);
		else
			u8s[0] = *s;
		s++;
		u8s[1] = '\0';
	} else if ((s + sz) > slast) {
		*errnum = EINVAL;

		for (i = 0; s < slast; )
			u8s[i++] = *s++;
		u8s[i] = '\0';

		*source = s;

		return (i);
	} else {
		if (is_it_toupper || is_it_tolower) {
			i = do_case_conv(uv, u8s, s, sz, is_it_toupper);
			s += sz;
			sz = i;
		} else {
			for (i = 0; i < sz; )
				u8s[i++] = *s++;
			u8s[i] = '\0';
		}
	}

	/*
	 * And then canonical/compatibility decomposition followed by
	 * an optional canonical composition. Please be noted that
	 * canonical composition is done only when a decomposition is
	 * done.
	 */
	if (canonical_decomposition || compatibility_decomposition) {
		if (sz == 1) {
			*state = U8_STATE_START;

			saved_sz = 1;

			comb_class[0] = 0;
			start[0] = 0;
			disp[0] = 1;

			last = 1;
		} else {
			saved_sz = do_decomp(uv, u8s, u8s, sz,
			    canonical_decomposition, state);

			last = 0;

			for (i = 0; i < saved_sz; ) {
				sz = u8_number_of_bytes[u8s[i]];

				comb_class[last] = combining_class(uv,
				    u8s + i, sz);
				start[last] = i;
				disp[last] = sz;

				last++;
				i += sz;
			}

			/*
			 * Decomposition yields various Hangul related
			 * states but not on combining marks. We need to
			 * find out at here by checking on the last
			 * character.
			 */
			if (*state == U8_STATE_START) {
				if (comb_class[last - 1])
					*state = U8_STATE_COMBINING_MARK;
			}
		}

		saved_last = last;

		while (s < slast) {
			sz = u8_number_of_bytes[*s];

			/*
			 * If this is an illegal character, an incomplete
			 * character, or an 7-bit ASCII Starter character,
			 * then we have collected a sequence; break and let
			 * the next call deal with the two cases.
			 *
			 * Note that this is okay only if you are using this
			 * function with a fixed length string, not on
			 * a buffer with multiple calls of one chunk at a time.
			 */
			if (sz <= 1) {
				break;
			} else if ((s + sz) > slast) {
				break;
			} else {
				/*
				 * If the previous character was a Hangul Jamo
				 * and this character is a Hangul Jamo that
				 * can be conjoined, we collect the Jamo.
				 */
				if (*s == U8_HANGUL_JAMO_1ST_BYTE) {
					U8_PUT_3BYTES_INTO_UTF32(u1,
					    *s, *(s + 1), *(s + 2));

					if (U8_HANGUL_COMPOSABLE_L_V(*state,
					    u1)) {
						i = 0;
						*state = U8_STATE_HANGUL_LV;
						goto COLLECT_A_HANGUL;
					}

					if (U8_HANGUL_COMPOSABLE_LV_T(*state,
					    u1)) {
						i = 0;
						*state = U8_STATE_HANGUL_LVT;
						goto COLLECT_A_HANGUL;
					}
				}

				/*
				 * Regardless of whatever it was, if this is
				 * a Starter, we don't collect the character
				 * since that's a new start and we will deal
				 * with it at the next time.
				 */
				i = combining_class(uv, s, sz);
				if (i == U8_COMBINING_CLASS_STARTER)
					break;

				/*
				 * We know the current character is a combining
				 * mark. If the previous character wasn't
				 * a Starter (not Hangul) or a combining mark,
				 * then, we don't collect this combining mark.
				 */
				if (*state != U8_STATE_START &&
				    *state != U8_STATE_COMBINING_MARK)
					break;

				*state = U8_STATE_COMBINING_MARK;
COLLECT_A_HANGUL:
				/*
				 * If we collected a Starter and combining
				 * marks up to 30, i.e., total 31 characters,
				 * then, we terminate this degenerately long
				 * combining sequence with a U+034F COMBINING
				 * GRAPHEME JOINER (CGJ) which is 0xCD 0x8F in
				 * UTF-8 and turn this into a Stream-Safe
				 * Text. This will be extremely rare but
				 * possible.
				 *
				 * The following will also guarantee that
				 * we are not writing more than 32 characters
				 * plus a NULL at u8s[].
				 */
				if (last >= U8_UPPER_LIMIT_IN_A_SEQ) {
TURN_STREAM_SAFE:
					*state = U8_STATE_START;
					comb_class[last] = 0;
					start[last] = saved_sz;
					disp[last] = 2;
					last++;

					u8s[saved_sz++] = 0xCD;
					u8s[saved_sz++] = 0x8F;

					break;
				}

				/*
				 * Some combining marks also do decompose into
				 * another combining mark or marks.
				 */
				if (*state == U8_STATE_COMBINING_MARK) {
					k = last;
					l = sz;
					i = do_decomp(uv, uts, s, sz,
					    canonical_decomposition, state);
					for (j = 0; j < i; ) {
						sz = u8_number_of_bytes[uts[j]];

						comb_class[last] =
						    combining_class(uv,
						    uts + j, sz);
						start[last] = saved_sz + j;
						disp[last] = sz;

						last++;
						if (last >=
						    U8_UPPER_LIMIT_IN_A_SEQ) {
							last = k;
							goto TURN_STREAM_SAFE;
						}
						j += sz;
					}

					*state = U8_STATE_COMBINING_MARK;
					sz = i;
					s += l;

					for (i = 0; i < sz; i++)
						u8s[saved_sz++] = uts[i];
				} else {
					comb_class[last] = i;
					start[last] = saved_sz;
					disp[last] = sz;
					last++;

					for (i = 0; i < sz; i++)
						u8s[saved_sz++] = *s++;
				}

				/*
				 * If this is U+0345 COMBINING GREEK
				 * YPOGEGRAMMENI (0xCD 0x85 in UTF-8), a.k.a.,
				 * iota subscript, and need to be converted to
				 * uppercase letter, convert it to U+0399 GREEK
				 * CAPITAL LETTER IOTA (0xCE 0x99 in UTF-8),
				 * i.e., convert to capital adscript form as
				 * specified in the Unicode standard.
				 *
				 * This is the only special case of (ambiguous)
				 * case conversion at combining marks and
				 * probably the standard will never have
				 * anything similar like this in future.
				 */
				if (is_it_toupper && sz >= 2 &&
				    u8s[saved_sz - 2] == 0xCD &&
				    u8s[saved_sz - 1] == 0x85) {
					u8s[saved_sz - 2] = 0xCE;
					u8s[saved_sz - 1] = 0x99;
				}
			}
		}

		/*
		 * Let's try to ensure a canonical ordering for the collected
		 * combining marks. We do this only if we have collected
		 * at least one more non-Starter. (The decomposition mapping
		 * data tables have fully (and recursively) expanded and
		 * canonically ordered decompositions.)
		 *
		 * The U8_SWAP_COMB_MARKS() convenience macro has some
		 * assumptions and we are meeting the assumptions.
		 */
		last--;
		if (last >= saved_last) {
			for (i = 0; i < last; i++)
				for (j = last; j > i; j--)
					if (comb_class[j] &&
					    comb_class[j - 1] > comb_class[j]) {
						U8_SWAP_COMB_MARKS(j - 1, j);
					}
		}

		*source = s;

		if (! canonical_composition) {
			u8s[saved_sz] = '\0';
			return (saved_sz);
		}

		/*
		 * Now do the canonical composition. Note that we do this
		 * only after a canonical or compatibility decomposition to
		 * finish up NFC or NFKC.
		 */
		sz = do_composition(uv, u8s, comb_class, start, disp, last,
		    &s, slast);
	}

	*source = s;

	return ((size_t)sz);
}