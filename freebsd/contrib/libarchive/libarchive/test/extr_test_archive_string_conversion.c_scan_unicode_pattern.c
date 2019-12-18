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
typedef  int wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  unicode_to_utf16be (char*,unsigned int) ; 
 int /*<<< orphan*/  unicode_to_utf16le (char*,unsigned int) ; 
 int /*<<< orphan*/  unicode_to_utf8 (char*,unsigned int) ; 
 int /*<<< orphan*/  unicode_to_wc (int*,unsigned int) ; 

__attribute__((used)) static int
scan_unicode_pattern(char *out, wchar_t *wout, char *u16be, char *u16le,
    const char *pattern, int mac_nfd)
{
	unsigned uc = 0;
	const char *p = pattern;
	char *op = out;
	wchar_t *owp = wout;
	char *op16be = u16be;
	char *op16le = u16le;
	int ret = 0;

	for (;;) {
		if (*p >= '0' && *p <= '9')
			uc = (uc << 4) + (*p - '0');
		else if (*p >= 'A' && *p <= 'F')
			uc = (uc << 4) + (*p - 'A' + 0x0a);
		else {
			if (mac_nfd && op == out) {
				/*
				 * These are not converted to NFD on Mac OS.
 				 * U+2000 - U+2FFF
				 * U+F900 - U+FAFF
				 * U+2F800 - U+2FAFF
				 */
				switch (uc) {
				case 0x2194: case 0x219A: case 0x219B:
				case 0x21AE: case 0x21CD: case 0x21CE:
				case 0x21CF: case 0x2204: case 0x2209:
				case 0x220C: case 0x2224: case 0x2226:
				case 0x2241: case 0x2244: case 0x2247:
				case 0x2249: case 0x2260: case 0x2262:
				case 0x226D: case 0x226E: case 0x226F:
				case 0x2270: case 0x2271: case 0x2274:
				case 0x2275: case 0x2276: case 0x2278:
				case 0x2279: case 0x227A: case 0x227B:
				case 0x2280: case 0x2281: case 0x2284:
				case 0x2285: case 0x2288: case 0x2289:
				case 0x22AC: case 0x22AD: case 0x22AE:
				case 0x22AF: case 0x22E0: case 0x22E1:
				case 0x22E2: case 0x22E3: case 0x22EA:
				case 0x22EB: case 0x22EC: case 0x22ED:
				
				/*
				 * Those code points are not converted to
				 * NFD on Mac OS. I do not know the reason
				 * because it is undocumented.
				 *   NFC        NFD
				 *   1109A  ==> 11099 110BA
				 *   1109C  ==> 1109B 110BA
				 *   110AB  ==> 110A5 110BA
				 */
				case 0x1109A: case 0x1109C: case 0x110AB:
					ret = 1;
					break;
				}
			}
			op16be += unicode_to_utf16be(op16be, uc);
			op16le += unicode_to_utf16le(op16le, uc);
			owp += unicode_to_wc(owp, uc);
			op += unicode_to_utf8(op, uc);
			if (!*p) {
				*op16be++ = 0;
				*op16be = 0;
				*op16le++ = 0;
				*op16le = 0;
				*owp = L'\0';
				*op = '\0';
				break;
			}
			uc = 0;
		}
		p++;
	}
	return (ret);
}