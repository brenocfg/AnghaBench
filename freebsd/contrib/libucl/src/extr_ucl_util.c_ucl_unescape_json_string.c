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

/* Variables and functions */
 int /*<<< orphan*/  isdigit (char) ; 

size_t
ucl_unescape_json_string (char *str, size_t len)
{
	char *t = str, *h = str;
	int i, uval;

	if (len <= 1) {
		return len;
	}
	/* t is target (tortoise), h is source (hare) */

	while (len) {
		if (*h == '\\') {
			h ++;

			if (len == 1) {
				/*
				 * If \ is last, then do not try to go further
				 * Issue: #74
				 */
				len --;
				*t++ = '\\';
				continue;
			}

			switch (*h) {
			case 'n':
				*t++ = '\n';
				break;
			case 'r':
				*t++ = '\r';
				break;
			case 'b':
				*t++ = '\b';
				break;
			case 't':
				*t++ = '\t';
				break;
			case 'f':
				*t++ = '\f';
				break;
			case '\\':
				*t++ = '\\';
				break;
			case '"':
				*t++ = '"';
				break;
			case 'u':
				/* Unicode escape */
				uval = 0;
				h ++; /* u character */
				len --;

				if (len > 3) {
					for (i = 0; i < 4; i++) {
						uval <<= 4;
						if (isdigit (h[i])) {
							uval += h[i] - '0';
						}
						else if (h[i] >= 'a' && h[i] <= 'f') {
							uval += h[i] - 'a' + 10;
						}
						else if (h[i] >= 'A' && h[i] <= 'F') {
							uval += h[i] - 'A' + 10;
						}
						else {
							break;
						}
					}

					/* Encode */
					if(uval < 0x80) {
						t[0] = (char)uval;
						t ++;
					}
					else if(uval < 0x800) {
						t[0] = 0xC0 + ((uval & 0x7C0) >> 6);
						t[1] = 0x80 + ((uval & 0x03F));
						t += 2;
					}
					else if(uval < 0x10000) {
						t[0] = 0xE0 + ((uval & 0xF000) >> 12);
						t[1] = 0x80 + ((uval & 0x0FC0) >> 6);
						t[2] = 0x80 + ((uval & 0x003F));
						t += 3;
					}
#if 0
					/* It's not actually supported now */
					else if(uval <= 0x10FFFF) {
						t[0] = 0xF0 + ((uval & 0x1C0000) >> 18);
						t[1] = 0x80 + ((uval & 0x03F000) >> 12);
						t[2] = 0x80 + ((uval & 0x000FC0) >> 6);
						t[3] = 0x80 + ((uval & 0x00003F));
						t += 4;
					}
#endif
					else {
						*t++ = '?';
					}

					/* Consume 4 characters of source */
					h += 4;
					len -= 4;

					if (len > 0) {
						len --; /* for '\' character */
					}
					continue;
				}
				else {
					*t++ = 'u';
				}
				break;
			default:
				*t++ = *h;
				break;
			}
			h ++;
			len --;
		}
		else {
			*t++ = *h++;
		}

		if (len > 0) {
			len --;
		}
	}
	*t = '\0';

	return (t - str);
}