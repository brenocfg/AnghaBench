#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char revision; char* eisaid; char* serial; char* class; char* compat; char* description; int neisaid; int nserial; int nclass; int ncompat; int ndescription; } ;
typedef  TYPE_1__ pnpid_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  debug (char*,int,...) ; 
 int /*<<< orphan*/  logwarnx (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 void* strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
pnpparse(pnpid_t *id, char *buf, int len)
{
    char s[3];
    int offset;
    int sum = 0;
    int i, j;

    id->revision = 0;
    id->eisaid = NULL;
    id->serial = NULL;
    id->class = NULL;
    id->compat = NULL;
    id->description = NULL;
    id->neisaid = 0;
    id->nserial = 0;
    id->nclass = 0;
    id->ncompat = 0;
    id->ndescription = 0;

    if ((buf[0] != 0x28) && (buf[0] != 0x08)) {
	/* non-PnP mice */
	switch(buf[0]) {
	default:
	    return (FALSE);
	case 'M': /* Microsoft */
	    id->eisaid = "PNP0F01";
	    break;
	case 'H': /* MouseSystems */
	    id->eisaid = "PNP0F04";
	    break;
	}
	id->neisaid = strlen(id->eisaid);
	id->class = "MOUSE";
	id->nclass = strlen(id->class);
	debug("non-PnP mouse '%c'", buf[0]);
	return (TRUE);
    }

    /* PnP mice */
    offset = 0x28 - buf[0];

    /* calculate checksum */
    for (i = 0; i < len - 3; ++i) {
	sum += buf[i];
	buf[i] += offset;
    }
    sum += buf[len - 1];
    for (; i < len; ++i)
	buf[i] += offset;
    debug("PnP ID string: '%*.*s'", len, len, buf);

    /* revision */
    buf[1] -= offset;
    buf[2] -= offset;
    id->revision = ((buf[1] & 0x3f) << 6) | (buf[2] & 0x3f);
    debug("PnP rev %d.%02d", id->revision / 100, id->revision % 100);

    /* EISA vender and product ID */
    id->eisaid = &buf[3];
    id->neisaid = 7;

    /* option strings */
    i = 10;
    if (buf[i] == '\\') {
	/* device serial # */
	for (j = ++i; i < len; ++i) {
	    if (buf[i] == '\\')
		break;
	}
	if (i >= len)
	    i -= 3;
	if (i - j == 8) {
	    id->serial = &buf[j];
	    id->nserial = 8;
	}
    }
    if (buf[i] == '\\') {
	/* PnP class */
	for (j = ++i; i < len; ++i) {
	    if (buf[i] == '\\')
		break;
	}
	if (i >= len)
	    i -= 3;
	if (i > j + 1) {
	    id->class = &buf[j];
	    id->nclass = i - j;
	}
    }
    if (buf[i] == '\\') {
	/* compatible driver */
	for (j = ++i; i < len; ++i) {
	    if (buf[i] == '\\')
		break;
	}
	/*
	 * PnP COM spec prior to v0.96 allowed '*' in this field,
	 * it's not allowed now; just igore it.
	 */
	if (buf[j] == '*')
	    ++j;
	if (i >= len)
	    i -= 3;
	if (i > j + 1) {
	    id->compat = &buf[j];
	    id->ncompat = i - j;
	}
    }
    if (buf[i] == '\\') {
	/* product description */
	for (j = ++i; i < len; ++i) {
	    if (buf[i] == ';')
		break;
	}
	if (i >= len)
	    i -= 3;
	if (i > j + 1) {
	    id->description = &buf[j];
	    id->ndescription = i - j;
	}
    }

    /* checksum exists if there are any optional fields */
    if ((id->nserial > 0) || (id->nclass > 0)
	|| (id->ncompat > 0) || (id->ndescription > 0)) {
	debug("PnP checksum: 0x%X", sum);
	sprintf(s, "%02X", sum & 0x0ff);
	if (strncmp(s, &buf[len - 3], 2) != 0) {
#if 0
	    /*
	     * I found some mice do not comply with the PnP COM device
	     * spec regarding checksum... XXX
	     */
	    logwarnx("PnP checksum error", 0);
	    return (FALSE);
#endif
	}
    }

    return (TRUE);
}