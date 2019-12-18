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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CONT (unsigned char const) ; 
 int UNICODE_UTF8_LATIN1_FALLBACK ; 

size_t
utf8_to_utf16(uint16_t *dst, size_t dst_len,
	      const char *src, size_t src_len,
	      int flags, int *errp)
{
    const unsigned char *s;
    size_t spos, dpos;
    int error;
    uint16_t c;

#define IS_CONT(c)	(((c)&0xc0) == 0x80)

    error = 0;
    s = (const unsigned char *)src;
    spos = dpos = 0;
    while (spos<src_len) {
	if (s[spos] < 0x80)
	    c = s[spos++];
	else if ((flags & UNICODE_UTF8_LATIN1_FALLBACK)
		 && (spos >= src_len || !IS_CONT(s[spos+1]))
		 && s[spos]>=0xa0) {
	    /* not valid UTF-8, assume ISO 8859-1 */
	    c = s[spos++];
	}
	else if (s[spos] < 0xc0 || s[spos] >= 0xf5) {
	    /* continuation byte without lead byte
	       or lead byte for codepoint above 0x10ffff */
	    error++;
	    spos++;
	    continue;
	}
	else if (s[spos] < 0xe0) {
	    if (spos >= src_len || !IS_CONT(s[spos+1])) {
		spos++;
		error++;
		continue;
	    }
	    c = ((s[spos] & 0x3f) << 6) | (s[spos+1] & 0x3f);
	    spos += 2;
	    if (c < 0x80) {
		/* overlong encoding */
		error++;
		continue;
	    }
	}
	else if (s[spos] < 0xf0) {
	    if (spos >= src_len-2
		|| !IS_CONT(s[spos+1]) || !IS_CONT(s[spos+2])) {
		spos++;
		error++;
		continue;
	    }
	    c = ((s[spos] & 0x0f) << 12) | ((s[spos+1] & 0x3f) << 6)
		| (s[spos+2] & 0x3f);
	    spos += 3;
	    if (c < 0x800 || (c & 0xdf00) == 0xd800 ) {
		/* overlong encoding or encoded surrogate */
		error++;
		continue;
	    }
	}
	else {
	    uint32_t cc;
	    /* UTF-16 surrogate pair */

	    if (spos >= src_len-3 || !IS_CONT(s[spos+1])
		|| !IS_CONT(s[spos+2]) || !IS_CONT(s[spos+3])) {
		spos++;
		error++;
		
		continue;
	    }
	    cc = ((s[spos] & 0x03) << 18) | ((s[spos+1] & 0x3f) << 12)
		 | ((s[spos+2] & 0x3f) << 6) | (s[spos+3] & 0x3f);
	    spos += 4;
	    if (cc < 0x10000) {
		/* overlong encoding */
		error++;
		continue;
	    }
	    if (dst && dpos < dst_len)
		dst[dpos] = (0xd800 | ((cc-0x10000)>>10));
	    dpos++;
	    c = 0xdc00 | ((cc-0x10000) & 0x3ffff);
	}

	if (dst && dpos < dst_len)
	    dst[dpos] = c;
	dpos++;
    }
    
    if (errp)
	*errp = error;

    return dpos;

#undef IS_CONT
}