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
struct buf {char const* buf; } ;

/* Variables and functions */
 int MPARSE_LATIN1 ; 
 int MPARSE_UTF8 ; 
 int /*<<< orphan*/  assert (unsigned char const) ; 
 scalar_t__ snprintf (char const*,int,char*,unsigned char) ; 

int
preconv_encode(const struct buf *ib, size_t *ii, struct buf *ob, size_t *oi,
    int *filenc)
{
	const unsigned char	*cu;
	int			 nby;
	unsigned int		 accum;

	cu = (const unsigned char *)ib->buf + *ii;
	assert(*cu & 0x80);

	if ( ! (*filenc & MPARSE_UTF8))
		goto latin;

	nby = 1;
	while (nby < 5 && *cu & (1 << (7 - nby)))
		nby++;

	switch (nby) {
	case 2:
		accum = *cu & 0x1f;
		if (accum < 0x02)  /* Obfuscated ASCII. */
			goto latin;
		break;
	case 3:
		accum = *cu & 0x0f;
		break;
	case 4:
		accum = *cu & 0x07;
		if (accum > 0x04) /* Beyond Unicode. */
			goto latin;
		break;
	default:  /* Bad sequence header. */
		goto latin;
	}

	cu++;
	switch (nby) {
	case 3:
		if ((accum == 0x00 && ! (*cu & 0x20)) ||  /* Use 2-byte. */
		    (accum == 0x0d && *cu & 0x20))  /* Surrogates. */
			goto latin;
		break;
	case 4:
		if ((accum == 0x00 && ! (*cu & 0x30)) ||  /* Use 3-byte. */
		    (accum == 0x04 && *cu & 0x30))  /* Beyond Unicode. */
			goto latin;
		break;
	default:
		break;
	}

	while (--nby) {
		if ((*cu & 0xc0) != 0x80)  /* Invalid continuation. */
			goto latin;
		accum <<= 6;
		accum += *cu & 0x3f;
		cu++;
	}

	assert(accum > 0x7f);
	assert(accum < 0x110000);
	assert(accum < 0xd800 || accum > 0xdfff);

	*oi += snprintf(ob->buf + *oi, 11, "\\[u%.4X]", accum);
	*ii = (const char *)cu - ib->buf;
	*filenc &= ~MPARSE_LATIN1;
	return 1;

latin:
	if ( ! (*filenc & MPARSE_LATIN1))
		return 0;

	*oi += snprintf(ob->buf + *oi, 11,
	    "\\[u%.4X]", (unsigned char)ib->buf[(*ii)++]);

	*filenc &= ~MPARSE_UTF8;
	return 1;
}