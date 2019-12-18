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
typedef  int u_char ;

/* Variables and functions */
 scalar_t__ T ; 
 scalar_t__* text_chars ; 

int
looks_utf8(const char *ibuf, size_t nbytes)
{
	const u_char *buf = (u_char *)ibuf;
	size_t i;
	int n;
	int gotone = 0, ctrl = 0;

	for (i = 0; i < nbytes; i++) {
		if ((buf[i] & 0x80) == 0) {	   /* 0xxxxxxx is plain ASCII */
			/*
			 * Even if the whole file is valid UTF-8 sequences,
			 * still reject it if it uses weird control characters.
			 */

			if (text_chars[buf[i]] != T)
				ctrl = 1;
		} else if ((buf[i] & 0x40) == 0) { /* 10xxxxxx never 1st byte */
			return -1;
		} else {			   /* 11xxxxxx begins UTF-8 */
			int following;

			if ((buf[i] & 0x20) == 0)	/* 110xxxxx */
				if (buf[i] > 0xC1)	/* C0, C1 */
					following = 1;
				else return -1;
			else if ((buf[i] & 0x10) == 0)	/* 1110xxxx */
				following = 2;
			else if ((buf[i] & 0x08) == 0)	/* 11110xxx */
				if (buf[i] < 0xF5)
					following = 3;
				else return -1;		/* F5, F6, F7 */
			else
				return -1;		/* F8~FF */

			for (n = 0; n < following; n++) {
				i++;
				if (i >= nbytes)
					goto done;

				if ((buf[i] & 0xc0) != 0x80)	/* 10xxxxxx */
					return -1;
			}

			gotone = 1;
		}
	}
done:
	return ctrl ? 0 : (gotone ? 2 : 1);
}