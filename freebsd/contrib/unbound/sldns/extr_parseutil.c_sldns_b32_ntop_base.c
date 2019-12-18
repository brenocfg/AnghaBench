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
typedef  int uint8_t ;

/* Variables and functions */
 size_t sldns_b32_ntop_calculate_size (size_t) ; 
 size_t sldns_b32_ntop_calculate_size_no_padding (size_t) ; 

__attribute__((used)) static int
sldns_b32_ntop_base(const uint8_t* src, size_t src_sz, char* dst, size_t dst_sz,
	int extended_hex, int add_padding)
{
	size_t ret_sz;
	const char* b32 = extended_hex ?  "0123456789abcdefghijklmnopqrstuv"
					: "abcdefghijklmnopqrstuvwxyz234567";

	size_t c = 0; /* c is used to carry partial base32 character over 
		       * byte boundaries for sizes with a remainder.
		       * (i.e. src_sz % 5 != 0)
		       */

	ret_sz = add_padding ? sldns_b32_ntop_calculate_size(src_sz)
			     : sldns_b32_ntop_calculate_size_no_padding(src_sz);
	
	/* Do we have enough space? */
	if (dst_sz < ret_sz + 1)
		return -1;

	/* We know the size; terminate the string */
	dst[ret_sz] = '\0';

	/* First process all chunks of five */
	while (src_sz >= 5) {
		/* 00000... ........ ........ ........ ........ */
		dst[0] = b32[(src[0]       ) >> 3];

		/* .....111 11...... ........ ........ ........ */
		dst[1] = b32[(src[0] & 0x07) << 2 | src[1] >> 6];

		/* ........ ..22222. ........ ........ ........ */
		dst[2] = b32[(src[1] & 0x3e) >> 1];

		/* ........ .......3 3333.... ........ ........ */
		dst[3] = b32[(src[1] & 0x01) << 4 | src[2] >> 4];

		/* ........ ........ ....4444 4....... ........ */
		dst[4] = b32[(src[2] & 0x0f) << 1 | src[3] >> 7];

		/* ........ ........ ........ .55555.. ........ */
		dst[5] = b32[(src[3] & 0x7c) >> 2];

		/* ........ ........ ........ ......66 666..... */
		dst[6] = b32[(src[3] & 0x03) << 3 | src[4] >> 5];

		/* ........ ........ ........ ........ ...77777 */
		dst[7] = b32[(src[4] & 0x1f)     ];

		src_sz -= 5;
		src    += 5;
		dst    += 8;
	}
	/* Process what remains */
	switch (src_sz) {
	case 4: /* ........ ........ ........ ......66 666..... */
		dst[6] = b32[(src[3] & 0x03) << 3];

		/* ........ ........ ........ .55555.. ........ */
		dst[5] = b32[(src[3] & 0x7c) >> 2];

		/* ........ ........ ....4444 4....... ........ */
			 c =  src[3]         >> 7 ;
		/* fallthrough */
	case 3: dst[4] = b32[(src[2] & 0x0f) << 1 | c];

		/* ........ .......3 3333.... ........ ........ */
			 c =  src[2]         >> 4 ;
		/* fallthrough */
	case 2:	dst[3] = b32[(src[1] & 0x01) << 4 | c];

		/* ........ ..22222. ........ ........ ........ */
		dst[2] = b32[(src[1] & 0x3e) >> 1];

		/* .....111 11...... ........ ........ ........ */
			 c =  src[1]         >> 6 ;
		/* fallthrough */
	case 1:	dst[1] = b32[(src[0] & 0x07) << 2 | c];

		/* 00000... ........ ........ ........ ........ */
		dst[0] = b32[ src[0]         >> 3];
	}
	/* Add padding */
	if (add_padding) {
		switch (src_sz) {
			case 1: dst[2] = '=';
				dst[3] = '=';
				/* fallthrough */
			case 2: dst[4] = '=';
				/* fallthrough */
			case 3: dst[5] = '=';
				dst[6] = '=';
				/* fallthrough */
			case 4: dst[7] = '=';
		}
	}
	return (int)ret_sz;
}