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
 size_t CHUNK_SZ ; 
 char* memchr (char*,char,size_t) ; 

__attribute__((used)) static inline char *
find_eol_char(char *s, size_t len)
{
#define CHUNK_SZ 128
	/* Lots of benchmarking found this approach to be faster in practice
	 * than doing two memchrs over the whole buffer, doin a memchr on each
	 * char of the buffer, or trying to emulate memchr by hand. */
	char *s_end, *cr, *lf;
	s_end = s+len;
	while (s < s_end) {
		size_t chunk = (s + CHUNK_SZ < s_end) ? CHUNK_SZ : (s_end - s);
		cr = memchr(s, '\r', chunk);
		lf = memchr(s, '\n', chunk);
		if (cr) {
			if (lf && lf < cr)
				return lf;
			return cr;
		} else if (lf) {
			return lf;
		}
		s += CHUNK_SZ;
	}

	return NULL;
#undef CHUNK_SZ
}