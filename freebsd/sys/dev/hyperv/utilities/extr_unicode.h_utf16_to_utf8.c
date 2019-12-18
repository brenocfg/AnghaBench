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
typedef  size_t uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_BYTE (size_t const) ; 
 int /*<<< orphan*/  CHECK_LENGTH (int) ; 

size_t
utf16_to_utf8(char *dst, size_t dst_len,
	      const uint16_t *src, size_t src_len,
	      int flags, int *errp)
{
    uint16_t spos, dpos;
    int error;

#define CHECK_LENGTH(l)	(dpos > dst_len-(l) ? dst=NULL : NULL)
#define ADD_BYTE(b)	(dst ? dst[dpos] = (b) : 0, dpos++)

    error = 0;
    dpos = 0;
    for (spos=0; spos<src_len; spos++) {
	if (src[spos] < 0x80) {
	    CHECK_LENGTH(1);
	    ADD_BYTE(src[spos]);
	}
	else if (src[spos] < 0x800) {
	    CHECK_LENGTH(2);
	    ADD_BYTE(0xc0 | (src[spos]>>6));
	    ADD_BYTE(0x80 | (src[spos] & 0x3f));
	}
	else if ((src[spos] & 0xdc00) == 0xd800) {
	    uint32_t c;
	    /* first surrogate */
	    if (spos == src_len - 1 || (src[spos] & 0xdc00) != 0xdc00) {
		/* no second surrogate present */
		error++;
		continue;
	    }
	    spos++;
	    CHECK_LENGTH(4);
	    c = (((src[spos]&0x3ff) << 10) | (src[spos+1]&0x3ff)) + 0x10000;
	    ADD_BYTE(0xf0 | (c>>18));
	    ADD_BYTE(0x80 | ((c>>12) & 0x3f));
	    ADD_BYTE(0x80 | ((c>>6) & 0x3f));
	    ADD_BYTE(0x80 | (c & 0x3f));
	}
	else if ((src[spos] & 0xdc00) == 0xdc00) {
	    /* second surrogate without preceding first surrogate */
	    error++;
	}
	else {
	    CHECK_LENGTH(3);
	    ADD_BYTE(0xe0 | src[spos]>>12);
	    ADD_BYTE(0x80 | ((src[spos]>>6) & 0x3f));
	    ADD_BYTE(0x80 | (src[spos] & 0x3f));
	}
    }

    if (errp)
	*errp = error;

    return dpos;

#undef ADD_BYTE
#undef CHECK_LENGTH
}