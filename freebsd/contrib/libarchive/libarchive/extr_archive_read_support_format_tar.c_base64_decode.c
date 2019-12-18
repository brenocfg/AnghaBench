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
typedef  int /*<<< orphan*/  digits ;
typedef  int /*<<< orphan*/  decode_table ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 

__attribute__((used)) static char *
base64_decode(const char *s, size_t len, size_t *out_len)
{
	static const unsigned char digits[64] = {
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
		'O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b',
		'c','d','e','f','g','h','i','j','k','l','m','n','o','p',
		'q','r','s','t','u','v','w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9','+','/' };
	static unsigned char decode_table[128];
	char *out, *d;
	const unsigned char *src = (const unsigned char *)s;

	/* If the decode table is not yet initialized, prepare it. */
	if (decode_table[digits[1]] != 1) {
		unsigned i;
		memset(decode_table, 0xff, sizeof(decode_table));
		for (i = 0; i < sizeof(digits); i++)
			decode_table[digits[i]] = i;
	}

	/* Allocate enough space to hold the entire output. */
	/* Note that we may not use all of this... */
	out = (char *)malloc(len - len / 4 + 1);
	if (out == NULL) {
		*out_len = 0;
		return (NULL);
	}
	d = out;

	while (len > 0) {
		/* Collect the next group of (up to) four characters. */
		int v = 0;
		int group_size = 0;
		while (group_size < 4 && len > 0) {
			/* '=' or '_' padding indicates final group. */
			if (*src == '=' || *src == '_') {
				len = 0;
				break;
			}
			/* Skip illegal characters (including line breaks) */
			if (*src > 127 || *src < 32
			    || decode_table[*src] == 0xff) {
				len--;
				src++;
				continue;
			}
			v <<= 6;
			v |= decode_table[*src++];
			len --;
			group_size++;
		}
		/* Align a short group properly. */
		v <<= 6 * (4 - group_size);
		/* Unpack the group we just collected. */
		switch (group_size) {
		case 4: d[2] = v & 0xff;
			/* FALLTHROUGH */
		case 3: d[1] = (v >> 8) & 0xff;
			/* FALLTHROUGH */
		case 2: d[0] = (v >> 16) & 0xff;
			break;
		case 1: /* this is invalid! */
			break;
		}
		d += group_size * 3 / 4;
	}

	*out_len = d - out;
	return (out);
}