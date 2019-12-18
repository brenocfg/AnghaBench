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
struct stat {int /*<<< orphan*/  st_size; } ;
struct simdisk_softc {int /*<<< orphan*/  sectors; int /*<<< orphan*/  sbuf; } ;
typedef  int /*<<< orphan*/  XML_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int MAP_NOCORE ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int XML_Parse (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XML_ParserCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XML_ParserFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetCharacterDataHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetElementHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (int /*<<< orphan*/ ,struct simdisk_softc*) ; 
 struct simdisk_softc* calloc (int,int) ; 
 int /*<<< orphan*/  characterData ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  endElement ; 
 int /*<<< orphan*/  err (int,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 char* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_new_auto () ; 
 int /*<<< orphan*/  startElement ; 

__attribute__((used)) static struct simdisk_softc *
g_simdisk_xml_load(const char *file)
{
	XML_Parser parser = XML_ParserCreate(NULL);
	struct stat st;
	char *p;
	struct simdisk_softc *sc;
	int fd, i;

	sc = calloc(1, sizeof *sc);
	sc->sbuf = sbuf_new_auto();
	LIST_INIT(&sc->sectors);
	XML_SetUserData(parser, sc);
	XML_SetElementHandler(parser, startElement, endElement);
	XML_SetCharacterDataHandler(parser, characterData);

	fd = open(file, O_RDONLY);
	if (fd < 0)
		err(1, file);
	fstat(fd, &st);
	p = mmap(NULL, st.st_size, PROT_READ, MAP_NOCORE|MAP_PRIVATE, fd, 0);
	i = XML_Parse(parser, p, st.st_size, 1);
	if (i != 1)
		errx(1, "XML_Parse complains: return %d", i);
	munmap(p, st.st_size);
	close(fd);
	XML_ParserFree(parser);
	return (sc);
}