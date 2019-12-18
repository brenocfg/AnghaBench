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
typedef  int uint16_t ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 

__attribute__((used)) static const u_char *
name_ptr(netdissect_options *ndo,
         const u_char *buf, int ofs, const u_char *maxbuf)
{
    const u_char *p;
    u_char c;

    p = buf + ofs;
    if (p >= maxbuf)
	return(NULL);	/* name goes past the end of the buffer */
    ND_TCHECK2(*p, 1);

    c = *p;

    /* XXX - this should use the same code that the DNS dissector does */
    if ((c & 0xC0) == 0xC0) {
	uint16_t l;

	ND_TCHECK2(*p, 2);
	if ((p + 1) >= maxbuf)
	    return(NULL);	/* name goes past the end of the buffer */
	l = EXTRACT_16BITS(p) & 0x3FFF;
	if (l == 0) {
	    /* We have a pointer that points to itself. */
	    return(NULL);
	}
	p = buf + l;
	if (p >= maxbuf)
	    return(NULL);	/* name goes past the end of the buffer */
	ND_TCHECK2(*p, 1);
    }
    return(p);

trunc:
    return(NULL);	/* name goes past the end of the buffer */
}