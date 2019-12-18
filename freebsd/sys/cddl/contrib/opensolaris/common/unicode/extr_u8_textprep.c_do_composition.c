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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uchar_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ U8_COMBINING_CLASS_STARTER ; 
 scalar_t__ U8_HANGUL_JAMO_1ST_BYTE ; 
 scalar_t__ U8_HANGUL_JAMO_L (int) ; 
 scalar_t__ U8_HANGUL_JAMO_L_FIRST ; 
 scalar_t__ U8_HANGUL_JAMO_T (int) ; 
 int U8_HANGUL_JAMO_T_FIRST ; 
 scalar_t__ U8_HANGUL_JAMO_V (int) ; 
 scalar_t__ U8_HANGUL_JAMO_V_FIRST ; 
 int U8_HANGUL_SYL_FIRST ; 
 int U8_HANGUL_T_COUNT ; 
 int U8_HANGUL_V_COUNT ; 
 int U8_MAX_CHARS_A_SEQ ; 
 int U8_MB_CUR_MAX ; 
 int /*<<< orphan*/  U8_PUT_3BYTES_INTO_UTF32 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  U8_SAVE_HANGUL_AS_UTF8 (scalar_t__*,int /*<<< orphan*/ ,int,int,int) ; 
 int U8_STREAM_SAFE_TEXT_MAX ; 
 scalar_t__ U8_TBL_ELEMENT_FILLER ; 
 size_t U8_UPPER_LIMIT_IN_A_SEQ ; 
 scalar_t__ blocked (scalar_t__*,size_t) ; 
 scalar_t__* find_composition_start (size_t,scalar_t__*,size_t) ; 
 size_t* u8_number_of_bytes ; 

__attribute__((used)) static size_t
do_composition(size_t uv, uchar_t *s, uchar_t *comb_class, uchar_t *start,
	uchar_t *disp, size_t last, uchar_t **os, uchar_t *oslast)
{
	uchar_t t[U8_STREAM_SAFE_TEXT_MAX + 1];
	uchar_t tc[U8_MB_CUR_MAX];
	uint8_t saved_marks[U8_MAX_CHARS_A_SEQ];
	size_t saved_marks_count;
	uchar_t *p;
	uchar_t *saved_p;
	uchar_t *q;
	size_t i;
	size_t saved_i;
	size_t j;
	size_t k;
	size_t l;
	size_t C;
	size_t saved_l;
	size_t size;
	uint32_t u1;
	uint32_t u2;
	boolean_t match_not_found = B_TRUE;

	/*
	 * This should never happen unless the callers are doing some strange
	 * and unexpected things.
	 *
	 * The "last" is the index pointing to the last character not last + 1.
	 */
	if (last >= U8_MAX_CHARS_A_SEQ)
		last = U8_UPPER_LIMIT_IN_A_SEQ;

	for (i = l = 0; i <= last; i++) {
		/*
		 * The last or any non-Starters at the beginning, we don't
		 * have any chance to do composition and so we just copy them
		 * to the temporary buffer.
		 */
		if (i >= last || comb_class[i] != U8_COMBINING_CLASS_STARTER) {
SAVE_THE_CHAR:
			p = s + start[i];
			size = disp[i];
			for (k = 0; k < size; k++)
				t[l++] = *p++;
			continue;
		}

		/*
		 * If this could be a start of Hangul Jamos, then, we try to
		 * conjoin them.
		 */
		if (s[start[i]] == U8_HANGUL_JAMO_1ST_BYTE) {
			U8_PUT_3BYTES_INTO_UTF32(u1, s[start[i]],
			    s[start[i] + 1], s[start[i] + 2]);
			U8_PUT_3BYTES_INTO_UTF32(u2, s[start[i] + 3],
			    s[start[i] + 4], s[start[i] + 5]);

			if (U8_HANGUL_JAMO_L(u1) && U8_HANGUL_JAMO_V(u2)) {
				u1 -= U8_HANGUL_JAMO_L_FIRST;
				u2 -= U8_HANGUL_JAMO_V_FIRST;
				u1 = U8_HANGUL_SYL_FIRST +
				    (u1 * U8_HANGUL_V_COUNT + u2) *
				    U8_HANGUL_T_COUNT;

				i += 2;
				if (i <= last) {
					U8_PUT_3BYTES_INTO_UTF32(u2,
					    s[start[i]], s[start[i] + 1],
					    s[start[i] + 2]);

					if (U8_HANGUL_JAMO_T(u2)) {
						u1 += u2 -
						    U8_HANGUL_JAMO_T_FIRST;
						i++;
					}
				}

				U8_SAVE_HANGUL_AS_UTF8(t + l, 0, 1, 2, u1);
				i--;
				l += 3;
				continue;
			}
		}

		/*
		 * Let's then find out if this Starter has composition
		 * mapping.
		 */
		p = find_composition_start(uv, s + start[i], disp[i]);
		if (p == NULL)
			goto SAVE_THE_CHAR;

		/*
		 * We have a Starter with composition mapping and the next
		 * character is a non-Starter. Let's try to find out if
		 * we can do composition.
		 */

		saved_p = p;
		saved_i = i;
		saved_l = l;
		saved_marks_count = 0;

TRY_THE_NEXT_MARK:
		q = s + start[++i];
		size = disp[i];

		/*
		 * The next for() loop compares the non-Starter pointed by
		 * 'q' with the possible (joinable) characters pointed by 'p'.
		 *
		 * The composition final table entry pointed by the 'p'
		 * looks like the following:
		 *
		 * +---+---+---+-...-+---+---+---+---+-...-+---+---+
		 * | C | b0| b2| ... | bn| F | B0| B1| ... | Bm| F |
		 * +---+---+---+-...-+---+---+---+---+-...-+---+---+
		 *
		 * where C is the count byte indicating the number of
		 * mapping pairs where each pair would be look like
		 * (b0-bn F, B0-Bm F). The b0-bn are the bytes of the second
		 * character of a canonical decomposition and the B0-Bm are
		 * the bytes of a matching composite character. The F is
		 * a filler byte after each character as the separator.
		 */

		match_not_found = B_TRUE;

		for (C = *p++; C > 0; C--) {
			for (k = 0; k < size; p++, k++)
				if (*p != q[k])
					break;

			/* Have we found it? */
			if (k >= size && *p == U8_TBL_ELEMENT_FILLER) {
				match_not_found = B_FALSE;

				l = saved_l;

				while (*++p != U8_TBL_ELEMENT_FILLER)
					t[l++] = *p;

				break;
			}

			/* We didn't find; skip to the next pair. */
			if (*p != U8_TBL_ELEMENT_FILLER)
				while (*++p != U8_TBL_ELEMENT_FILLER)
					;
			while (*++p != U8_TBL_ELEMENT_FILLER)
				;
			p++;
		}

		/*
		 * If there was no match, we will need to save the combining
		 * mark for later appending. After that, if the next one
		 * is a non-Starter and not blocked, then, we try once
		 * again to do composition with the next non-Starter.
		 *
		 * If there was no match and this was a Starter, then,
		 * this is a new start.
		 *
		 * If there was a match and a composition done and we have
		 * more to check on, then, we retrieve a new composition final
		 * table entry for the composite and then try to do the
		 * composition again.
		 */

		if (match_not_found) {
			if (comb_class[i] == U8_COMBINING_CLASS_STARTER) {
				i--;
				goto SAVE_THE_CHAR;
			}

			saved_marks[saved_marks_count++] = i;
		}

		if (saved_l == l) {
			while (i < last) {
				if (blocked(comb_class, i + 1))
					saved_marks[saved_marks_count++] = ++i;
				else
					break;
			}
			if (i < last) {
				p = saved_p;
				goto TRY_THE_NEXT_MARK;
			}
		} else if (i < last) {
			p = find_composition_start(uv, t + saved_l,
			    l - saved_l);
			if (p != NULL) {
				saved_p = p;
				goto TRY_THE_NEXT_MARK;
			}
		}

		/*
		 * There is no more composition possible.
		 *
		 * If there was no composition what so ever then we copy
		 * over the original Starter and then append any non-Starters
		 * remaining at the target string sequentially after that.
		 */

		if (saved_l == l) {
			p = s + start[saved_i];
			size = disp[saved_i];
			for (j = 0; j < size; j++)
				t[l++] = *p++;
		}

		for (k = 0; k < saved_marks_count; k++) {
			p = s + start[saved_marks[k]];
			size = disp[saved_marks[k]];
			for (j = 0; j < size; j++)
				t[l++] = *p++;
		}
	}

	/*
	 * If the last character is a Starter and if we have a character
	 * (possibly another Starter) that can be turned into a composite,
	 * we do so and we do so until there is no more of composition
	 * possible.
	 */
	if (comb_class[last] == U8_COMBINING_CLASS_STARTER) {
		p = *os;
		saved_l = l - disp[last];

		while (p < oslast) {
			size = u8_number_of_bytes[*p];
			if (size <= 1 || (p + size) > oslast)
				break;

			saved_p = p;

			for (i = 0; i < size; i++)
				tc[i] = *p++;

			q = find_composition_start(uv, t + saved_l,
			    l - saved_l);
			if (q == NULL) {
				p = saved_p;
				break;
			}

			match_not_found = B_TRUE;

			for (C = *q++; C > 0; C--) {
				for (k = 0; k < size; q++, k++)
					if (*q != tc[k])
						break;

				if (k >= size && *q == U8_TBL_ELEMENT_FILLER) {
					match_not_found = B_FALSE;

					l = saved_l;

					while (*++q != U8_TBL_ELEMENT_FILLER) {
						/*
						 * This is practically
						 * impossible but we don't
						 * want to take any chances.
						 */
						if (l >=
						    U8_STREAM_SAFE_TEXT_MAX) {
							p = saved_p;
							goto SAFE_RETURN;
						}
						t[l++] = *q;
					}

					break;
				}

				if (*q != U8_TBL_ELEMENT_FILLER)
					while (*++q != U8_TBL_ELEMENT_FILLER)
						;
				while (*++q != U8_TBL_ELEMENT_FILLER)
					;
				q++;
			}

			if (match_not_found) {
				p = saved_p;
				break;
			}
		}
SAFE_RETURN:
		*os = p;
	}

	/*
	 * Now we copy over the temporary string to the target string.
	 * Since composition always reduces the number of characters or
	 * the number of characters stay, we don't need to worry about
	 * the buffer overflow here.
	 */
	for (i = 0; i < l; i++)
		s[i] = t[i];
	s[l] = '\0';

	return (l);
}