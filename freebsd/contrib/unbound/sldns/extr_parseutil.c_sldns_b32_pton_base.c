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
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static int
sldns_b32_pton_base(const char* src, size_t src_sz, uint8_t* dst, size_t dst_sz,
	int extended_hex, int check_padding)
{
	size_t i = 0;
	char ch = '\0';
	uint8_t buf[8];
	uint8_t* start = dst;

	while (src_sz) {
		/* Collect 8 characters in buf (if possible) */
		for (i = 0; i < 8; i++) {

			do {
				ch = *src++;
				--src_sz;

			} while (isspace((unsigned char)ch) && src_sz > 0);

			if (ch == '=' || ch == '\0')
				break;

			else if (extended_hex)

				if (ch >= '0' && ch <= '9')
					buf[i] = (uint8_t)ch - '0';
				else if (ch >= 'a' && ch <= 'v')
					buf[i] = (uint8_t)ch - 'a' + 10;
				else if (ch >= 'A' && ch <= 'V')
					buf[i] = (uint8_t)ch - 'A' + 10;
				else
					return -1;

			else if (ch >= 'a' && ch <= 'z')
				buf[i] = (uint8_t)ch - 'a';
			else if (ch >= 'A' && ch <= 'Z')
				buf[i] = (uint8_t)ch - 'A';
			else if (ch >= '2' && ch <= '7')
				buf[i] = (uint8_t)ch - '2' + 26;
			else
				return -1;
		}
		/* Less that 8 characters. We're done. */
		if (i < 8)
			break;

		/* Enough space available at the destination? */
		if (dst_sz < 5)
			return -1;

		/* 00000... ........ ........ ........ ........ */
		/* .....111 11...... ........ ........ ........ */
		dst[0] = buf[0] << 3 | buf[1] >> 2;

		/* .....111 11...... ........ ........ ........ */
		/* ........ ..22222. ........ ........ ........ */
		/* ........ .......3 3333.... ........ ........ */
		dst[1] = buf[1] << 6 | buf[2] << 1 | buf[3] >> 4;

		/* ........ .......3 3333.... ........ ........ */
		/* ........ ........ ....4444 4....... ........ */
		dst[2] = buf[3] << 4 | buf[4] >> 1;

		/* ........ ........ ....4444 4....... ........ */
		/* ........ ........ ........ .55555.. ........ */
		/* ........ ........ ........ ......66 666..... */
		dst[3] = buf[4] << 7 | buf[5] << 2 | buf[6] >> 3;

		/* ........ ........ ........ ......66 666..... */
		/* ........ ........ ........ ........ ...77777 */
		dst[4] = buf[6] << 5 | buf[7];

		dst += 5;
		dst_sz -= 5;
	}
	/* Not ending on a eight byte boundary? */
	if (i > 0 && i < 8) {

		/* Enough space available at the destination? */
		if (dst_sz < (i + 1) / 2)
			return -1;

		switch (i) {
		case 7: /* ........ ........ ........ ......66 666..... */
			/* ........ ........ ........ .55555.. ........ */
			/* ........ ........ ....4444 4....... ........ */
			dst[3] = buf[4] << 7 | buf[5] << 2 | buf[6] >> 3;
			/* fallthrough */

		case 5: /* ........ ........ ....4444 4....... ........ */
			/* ........ .......3 3333.... ........ ........ */
			dst[2] = buf[3] << 4 | buf[4] >> 1;
			/* fallthrough */

		case 4: /* ........ .......3 3333.... ........ ........ */
			/* ........ ..22222. ........ ........ ........ */
			/* .....111 11...... ........ ........ ........ */
			dst[1] = buf[1] << 6 | buf[2] << 1 | buf[3] >> 4;
			/* fallthrough */

		case 2: /* .....111 11...... ........ ........ ........ */
			/* 00000... ........ ........ ........ ........ */
			dst[0] = buf[0] << 3 | buf[1] >> 2;

			break;

		default:
			return -1;
		}
		dst += (i + 1) / 2;

		if (check_padding) {
			/* Check remaining padding characters */
			if (ch != '=')
				return -1;

			/* One down, 8 - i - 1 more to come... */
			for (i = 8 - i - 1; i > 0; i--) {

				do {
					if (src_sz == 0)
						return -1;
					ch = *src++;
					src_sz--;

				} while (isspace((unsigned char)ch));

				if (ch != '=')
					return -1;
			}
		}
	}
	return dst - start;
}