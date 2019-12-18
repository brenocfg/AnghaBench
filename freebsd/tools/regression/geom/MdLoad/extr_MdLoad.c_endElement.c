#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct simdisk_softc {int sectorsize; int /*<<< orphan*/  sbuf; TYPE_1__* sp; void* fwcylinders; void* fwheads; void* fwsectors; scalar_t__ mediasize; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {int /*<<< orphan*/ * data; void* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  g_simdisk_insertsector (struct simdisk_softc*,TYPE_1__*) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  sbuf_clear (int /*<<< orphan*/ ) ; 
 char* sbuf_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 void* strtoul (char*,char**,int) ; 
 void* strtoull (char*,char**,int /*<<< orphan*/ ) ; 
 char tolower (char) ; 

__attribute__((used)) static void
endElement(void *userData, const char *name)
{
	struct simdisk_softc *sc;
	char *p;
	u_char *q;
	int i, j;
	off_t o;

	sc = userData;

	if (!strcasecmp(name, "comment")) {
		sbuf_clear(sc->sbuf);
		return;
	}
	sbuf_finish(sc->sbuf);
	if (!strcasecmp(name, "sectorsize")) {
		sc->sectorsize = strtoul(sbuf_data(sc->sbuf), &p, 0);
		if (*p != '\0')
			errx(1, "strtoul croaked on sectorsize");
	} else if (!strcasecmp(name, "mediasize")) {
		o = strtoull(sbuf_data(sc->sbuf), &p, 0);
		if (*p != '\0')
			errx(1, "strtoul croaked on mediasize");
		if (o > 0)
			sc->mediasize = o;
	} else if (!strcasecmp(name, "fwsectors")) {
		sc->fwsectors = strtoul(sbuf_data(sc->sbuf), &p, 0);
		if (*p != '\0')
			errx(1, "strtoul croaked on fwsectors");
	} else if (!strcasecmp(name, "fwheads")) {
		sc->fwheads = strtoul(sbuf_data(sc->sbuf), &p, 0);
		if (*p != '\0')
			errx(1, "strtoul croaked on fwheads");
	} else if (!strcasecmp(name, "fwcylinders")) {
		sc->fwcylinders = strtoul(sbuf_data(sc->sbuf), &p, 0);
		if (*p != '\0')
			errx(1, "strtoul croaked on fwcylinders");
	} else if (!strcasecmp(name, "offset")) {
		sc->sp->offset= strtoull(sbuf_data(sc->sbuf), &p, 0);
		if (*p != '\0')
			errx(1, "strtoul croaked on offset");
	} else if (!strcasecmp(name, "fill")) {
		j = strtoul(sbuf_data(sc->sbuf), NULL, 16);
		memset(sc->sp->data, j, sc->sectorsize);
	} else if (!strcasecmp(name, "hexdata")) {
		q = sc->sp->data;
		p = sbuf_data(sc->sbuf);
		for (i = 0; i < sc->sectorsize; i++) {
			if (!isxdigit(*p))
				errx(1, "I croaked on hexdata %d:(%02x)", i, *p);
			if (isdigit(*p))
				j = (*p - '0') << 4;
			else
				j = (tolower(*p) - 'a' + 10) << 4;
			p++;
			if (!isxdigit(*p))
				errx(1, "I croaked on hexdata %d:(%02x)", i, *p);
			if (isdigit(*p))
				j |= *p - '0';
			else
				j |= tolower(*p) - 'a' + 10;
			p++;
			*q++ = j;
		}
	} else if (!strcasecmp(name, "sector")) {
		g_simdisk_insertsector(sc, sc->sp);
		sc->sp = NULL;
	} else if (!strcasecmp(name, "diskimage")) {
	} else if (!strcasecmp(name, "FreeBSD")) {
	} else {
		printf("<%s>[[%s]]\n", name, sbuf_data(sc->sbuf));
	}
	sbuf_clear(sc->sbuf);
}