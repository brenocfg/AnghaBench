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
struct stat {int /*<<< orphan*/  st_size; } ;
struct mytree {TYPE_1__* top; TYPE_1__* cur; } ;
typedef  int /*<<< orphan*/  XML_Parser ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  cont; int /*<<< orphan*/  key; struct TYPE_2__* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CharData ; 
 int /*<<< orphan*/  EndElement ; 
 int MAP_NOCORE ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  StartElement ; 
 int XML_Parse (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XML_ParserCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XML_ParserFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetCharacterDataHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetElementHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XML_SetUserData (int /*<<< orphan*/ ,struct mytree*) ; 
 struct mytree* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 char* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_node () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_finish (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mytree *
dofile(char *filename)
{
	XML_Parser parser;
	struct mytree *mt;
	struct stat st;
	int fd;
	char *p;
	int i;

	parser = XML_ParserCreate(NULL);
	mt = calloc(1, sizeof *mt);
	mt->top = new_node();
	mt->top->name = "(top)";
	mt->top->parent = mt->top;
	mt->cur = mt->top;
	sbuf_finish(mt->top->key);
	sbuf_finish(mt->top->cont);
	XML_SetUserData(parser, mt);
	XML_SetElementHandler(parser, StartElement, EndElement);
	XML_SetCharacterDataHandler(parser, CharData);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err(1, filename);
	fstat(fd, &st);
	p = mmap(NULL, st.st_size, PROT_READ, MAP_NOCORE|MAP_PRIVATE, fd, 0);
	i = XML_Parse(parser, p, st.st_size, 1);
	if (i != 1)
		errx(1, "XML_Parse complained -> %d", i);
	munmap(p, st.st_size);
	close(fd);
	XML_ParserFree(parser);
	sbuf_finish(mt->top->cont);
	if (i)
		return (mt);
	else
		return (NULL);
}