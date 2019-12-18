#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  size_t uchar_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {size_t tbl_id; size_t base; } ;
struct TYPE_3__ {size_t tbl_id; size_t base; } ;

/* Variables and functions */
 size_t U8_ASCII_TOLOWER (size_t) ; 
 size_t U8_ASCII_TOUPPER (size_t) ; 
 size_t U8_MB_CUR_MAX ; 
 size_t U8_TBL_ELEMENT_NOT_DEF ; 
 size_t*** u8_case_common_b2_tbl ; 
 size_t** u8_common_b1_tbl ; 
 TYPE_2__*** u8_tolower_b3_tbl ; 
 size_t*** u8_tolower_b4_tbl ; 
 size_t** u8_tolower_final_tbl ; 
 TYPE_1__*** u8_toupper_b3_tbl ; 
 size_t*** u8_toupper_b4_tbl ; 
 size_t** u8_toupper_final_tbl ; 

__attribute__((used)) static size_t
do_case_conv(int uv, uchar_t *u8s, uchar_t *s, int sz, boolean_t is_it_toupper)
{
	size_t i;
	uint16_t b1 = 0;
	uint16_t b2 = 0;
	uint16_t b3 = 0;
	uint16_t b3_tbl;
	uint16_t b3_base;
	uint16_t b4 = 0;
	size_t start_id;
	size_t end_id;

	/*
	 * At this point, the only possible values for sz are 2, 3, and 4.
	 * The u8s should point to a vector that is well beyond the size of
	 * 5 bytes.
	 */
	if (sz == 2) {
		b3 = u8s[0] = s[0];
		b4 = u8s[1] = s[1];
	} else if (sz == 3) {
		b2 = u8s[0] = s[0];
		b3 = u8s[1] = s[1];
		b4 = u8s[2] = s[2];
	} else if (sz == 4) {
		b1 = u8s[0] = s[0];
		b2 = u8s[1] = s[1];
		b3 = u8s[2] = s[2];
		b4 = u8s[3] = s[3];
	} else {
		/* This is not possible but just in case as a fallback. */
		if (is_it_toupper)
			*u8s = U8_ASCII_TOUPPER(*s);
		else
			*u8s = U8_ASCII_TOLOWER(*s);
		u8s[1] = '\0';

		return (1);
	}
	u8s[sz] = '\0';

	/*
	 * Let's find out if we have a corresponding character.
	 */
	b1 = u8_common_b1_tbl[uv][b1];
	if (b1 == U8_TBL_ELEMENT_NOT_DEF)
		return ((size_t)sz);

	b2 = u8_case_common_b2_tbl[uv][b1][b2];
	if (b2 == U8_TBL_ELEMENT_NOT_DEF)
		return ((size_t)sz);

	if (is_it_toupper) {
		b3_tbl = u8_toupper_b3_tbl[uv][b2][b3].tbl_id;
		if (b3_tbl == U8_TBL_ELEMENT_NOT_DEF)
			return ((size_t)sz);

		start_id = u8_toupper_b4_tbl[uv][b3_tbl][b4];
		end_id = u8_toupper_b4_tbl[uv][b3_tbl][b4 + 1];

		/* Either there is no match or an error at the table. */
		if (start_id >= end_id || (end_id - start_id) > U8_MB_CUR_MAX)
			return ((size_t)sz);

		b3_base = u8_toupper_b3_tbl[uv][b2][b3].base;

		for (i = 0; start_id < end_id; start_id++)
			u8s[i++] = u8_toupper_final_tbl[uv][b3_base + start_id];
	} else {
		b3_tbl = u8_tolower_b3_tbl[uv][b2][b3].tbl_id;
		if (b3_tbl == U8_TBL_ELEMENT_NOT_DEF)
			return ((size_t)sz);

		start_id = u8_tolower_b4_tbl[uv][b3_tbl][b4];
		end_id = u8_tolower_b4_tbl[uv][b3_tbl][b4 + 1];

		if (start_id >= end_id || (end_id - start_id) > U8_MB_CUR_MAX)
			return ((size_t)sz);

		b3_base = u8_tolower_b3_tbl[uv][b2][b3].base;

		for (i = 0; start_id < end_id; start_id++)
			u8s[i++] = u8_tolower_final_tbl[uv][b3_base + start_id];
	}

	/*
	 * If i is still zero, that means there is no corresponding character.
	 */
	if (i == 0)
		return ((size_t)sz);

	u8s[i] = '\0';

	return (i);
}