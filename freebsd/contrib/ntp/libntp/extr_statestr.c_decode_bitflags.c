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
struct codestring {int code; char* string1; char* string0; } ;

/* Variables and functions */
 size_t LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int errno ; 
 struct codestring const* k_st_bits ; 
 struct codestring const* peer_st_bits ; 
 int snprintf (char*,size_t,char*,char const*,...) ; 

__attribute__((used)) static const char *
decode_bitflags(
	int				bits,
	const char *			sep2,
	const struct codestring *	tab,
	size_t				tab_ct
	)
{
	const char *	sep;
	char *		buf;
	char *		pch;
	char *		lim;
	size_t		b;
	int		rc;
	int		saved_errno;	/* for use in DPRINTF with %m */

	saved_errno = errno;
	LIB_GETBUF(buf);
	pch = buf;
	lim = buf + LIB_BUFLENGTH;
	sep = "";

	for (b = 0; b < tab_ct; b++) {
		const char * flagstr;

		if (tab[b].code & bits) {
			flagstr = tab[b].string1;
		} else {
			flagstr = tab[b].string0;
		}

		if (flagstr) {
			size_t avail = lim - pch;
			rc = snprintf(pch, avail, "%s%s", sep,
				      flagstr);
			if ((size_t)rc >= avail)
				goto toosmall;
			pch += rc;
			sep = sep2;
		}
	}

	return buf;

    toosmall:
	snprintf(buf, LIB_BUFLENGTH,
		 "decode_bitflags(%s) can't decode 0x%x in %d bytes",
		 (tab == peer_st_bits)
		     ? "peer_st"
		     : 
#ifdef KERNEL_PLL
		       (tab == k_st_bits)
			   ? "kern_st"
			   :
#endif
			     "",
		 bits, (int)LIB_BUFLENGTH);
	errno = saved_errno;

	return buf;
}