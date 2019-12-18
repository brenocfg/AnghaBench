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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  lbuf ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
dump_hex_printable(
	const void *	data,
	size_t		len
	)
{
	/* every line shows at most 16 bytes, so we need a buffer of
	 *   4 * 16 (2 xdigits, 1 char, one sep for xdigits)
	 * + 2 * 1  (block separators)
	 * + <LF> + <NUL>
	 *---------------
	 *  68 bytes
	 */
	static const char s_xdig[16] = "0123456789ABCDEF";

	char lbuf[68];
	int  ch, rowlen;
	const u_char * cdata = data;
	char *xptr, *pptr;

	while (len) {
		memset(lbuf, ' ', sizeof(lbuf));
		xptr = lbuf;
		pptr = lbuf + 3*16 + 2;

		rowlen = (len > 16) ? 16 : (int)len;
		len -= rowlen;
		
		do {
			ch = *cdata++;
			
			*xptr++ = s_xdig[ch >> 4  ];
			*xptr++ = s_xdig[ch & 0x0F];
			if (++xptr == lbuf + 3*8)
				++xptr;

			*pptr++ = isprint(ch) ? (char)ch : '.';
		} while (--rowlen);

		*pptr++ = '\n';
		*pptr   = '\0';
		fputs(lbuf, stdout);
	}
}