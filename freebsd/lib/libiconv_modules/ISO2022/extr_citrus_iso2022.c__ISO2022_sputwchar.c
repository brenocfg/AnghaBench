#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct TYPE_12__ {int gl; int gr; int singlegl; int singlegr; TYPE_1__* g; } ;
typedef  TYPE_2__ _ISO2022State ;
struct TYPE_13__ {int flags; TYPE_4__* initg; } ;
typedef  TYPE_3__ _ISO2022EncodingInfo ;
struct TYPE_14__ {int final; int interm; int type; } ;
typedef  TYPE_4__ _ISO2022Charset ;
struct TYPE_11__ {int type; int final; char interm; } ;

/* Variables and functions */
#define  CS94 131 
#define  CS94MULTI 130 
#define  CS96 129 
#define  CS96MULTI 128 
 int E2BIG ; 
 int EILSEQ ; 
 int F_8BIT ; 
 int F_LS0 ; 
 int F_LS1 ; 
 int F_LS1R ; 
 int F_LS2 ; 
 int F_LS2R ; 
 int F_LS3 ; 
 int F_LS3R ; 
 int F_NOOLD ; 
 int F_SS2 ; 
 int F_SS2R ; 
 int F_SS3 ; 
 int F_SS3R ; 
 int MB_LEN_MAX ; 
 TYPE_4__ ascii ; 
 scalar_t__ isc0 (int) ; 
 scalar_t__ isc1 (int) ; 
 int /*<<< orphan*/  iscntl (int) ; 
 TYPE_4__ iso88591 ; 
 int /*<<< orphan*/  isthree (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int recommendation (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ strchr (char*,int) ; 

__attribute__((used)) static int
_ISO2022_sputwchar(_ISO2022EncodingInfo * __restrict ei, wchar_t wc,
    char * __restrict string, size_t n, char ** __restrict result,
    _ISO2022State * __restrict psenc, size_t * __restrict nresult)
{
	_ISO2022Charset cs;
	char *p;
	char tmp[MB_LEN_MAX];
	size_t len;
	int bit8, i = 0, target;
	unsigned char mask;

	if (isc0(wc & 0xff)) {
		/* go back to INIT0 or ASCII on control chars */
		cs = ei->initg[0].final ? ei->initg[0] : ascii;
	} else if (isc1(wc & 0xff)) {
		/* go back to INIT1 or ISO-8859-1 on control chars */
		cs = ei->initg[1].final ? ei->initg[1] : iso88591;
	} else if (!(wc & ~0xff)) {
		if (wc & 0x80) {
			/* special treatment for ISO-8859-1 */
			cs = iso88591;
		} else {
			/* special treatment for ASCII */
			cs = ascii;
		}
	} else {
		cs.final = (wc >> 24) & 0x7f;
		if ((wc >> 16) & 0x80)
			cs.interm = (wc >> 16) & 0x7f;
		else
			cs.interm = '\0';
		if (wc & 0x80)
			cs.type = (wc & 0x00007f00) ? CS96MULTI : CS96;
		else
			cs.type = (wc & 0x00007f00) ? CS94MULTI : CS94;
	}
	target = recommendation(ei, &cs);
	p = tmp;
	bit8 = ei->flags & F_8BIT;

	/* designate the charset onto the target plane(G0/1/2/3). */
	if (psenc->g[target].type == cs.type &&
	    psenc->g[target].final == cs.final &&
	    psenc->g[target].interm == cs.interm)
		goto planeok;

	*p++ = '\033';
	if (cs.type == CS94MULTI || cs.type == CS96MULTI)
		*p++ = '$';
	if (target == 0 && cs.type == CS94MULTI && strchr("@AB", cs.final) &&
	    !cs.interm && !(ei->flags & F_NOOLD))
		;
	else if (cs.type == CS94 || cs.type == CS94MULTI)
		*p++ = "()*+"[target];
	else
		*p++ = ",-./"[target];
	if (cs.interm)
		*p++ = cs.interm;
	*p++ = cs.final;

	psenc->g[target].type = cs.type;
	psenc->g[target].final = cs.final;
	psenc->g[target].interm = cs.interm;

planeok:
	/* invoke the plane onto GL or GR. */
	if (psenc->gl == target)
		goto sideok;
	if (bit8 && psenc->gr == target)
		goto sideok;

	if (target == 0 && (ei->flags & F_LS0)) {
		*p++ = '\017';
		psenc->gl = 0;
	} else if (target == 1 && (ei->flags & F_LS1)) {
		*p++ = '\016';
		psenc->gl = 1;
	} else if (target == 2 && (ei->flags & F_LS2)) {
		*p++ = '\033';
		*p++ = 'n';
		psenc->gl = 2;
	} else if (target == 3 && (ei->flags & F_LS3)) {
		*p++ = '\033';
		*p++ = 'o';
		psenc->gl = 3;
	} else if (bit8 && target == 1 && (ei->flags & F_LS1R)) {
		*p++ = '\033';
		*p++ = '~';
		psenc->gr = 1;
	} else if (bit8 && target == 2 && (ei->flags & F_LS2R)) {
		*p++ = '\033';
		/*{*/
		*p++ = '}';
		psenc->gr = 2;
	} else if (bit8 && target == 3 && (ei->flags & F_LS3R)) {
		*p++ = '\033';
		*p++ = '|';
		psenc->gr = 3;
	} else if (target == 2 && (ei->flags & F_SS2)) {
		*p++ = '\033';
		*p++ = 'N';
		psenc->singlegl = 2;
	} else if (target == 3 && (ei->flags & F_SS3)) {
		*p++ = '\033';
		*p++ = 'O';
		psenc->singlegl = 3;
	} else if (bit8 && target == 2 && (ei->flags & F_SS2R)) {
		*p++ = '\216';
		*p++ = 'N';
		psenc->singlegl = psenc->singlegr = 2;
	} else if (bit8 && target == 3 && (ei->flags & F_SS3R)) {
		*p++ = '\217';
		*p++ = 'O';
		psenc->singlegl = psenc->singlegr = 3;
	} else
		goto ilseq;

sideok:
	if (psenc->singlegl == target)
		mask = 0x00;
	else if (psenc->singlegr == target)
		mask = 0x80;
	else if (psenc->gl == target)
		mask = 0x00;
	else if ((ei->flags & F_8BIT) && psenc->gr == target)
		mask = 0x80;
	else
		goto ilseq;

	switch (cs.type) {
	case CS94:
	case CS96:
		i = 1;
		break;
	case CS94MULTI:
	case CS96MULTI:
		i = !iscntl(wc & 0xff) ?
		    (isthree(cs.final) ? 3 : 2) : 1;
		break;
	}
	while (i-- > 0)
		*p++ = ((wc >> (i << 3)) & 0x7f) | mask;

	/* reset single shift state */
	psenc->singlegl = psenc->singlegr = -1;

	len = (size_t)(p - tmp);
	if (n < len) {
		if (result)
			*result = (char *)0;
		*nresult = (size_t)-1;
		return (E2BIG);
	}
	if (result)
		*result = string + len;
	memcpy(string, tmp, len);
	*nresult = len;

	return (0);

ilseq:
	*nresult = (size_t)-1;
	return (EILSEQ);
}