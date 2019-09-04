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
struct strbuf {int dummy; } ;
struct line {char* text; struct line* next; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  compare_strings ; 
 int /*<<< orphan*/  get_next ; 
 struct line* llist_mergesort (struct line*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  set_next ; 
 int /*<<< orphan*/  stdin ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ ,char) ; 
 struct line* xmalloc (int) ; 

int cmd__mergesort(int argc, const char **argv)
{
	struct line *line, *p = NULL, *lines = NULL;
	struct strbuf sb = STRBUF_INIT;

	for (;;) {
		if (strbuf_getwholeline(&sb, stdin, '\n'))
			break;
		line = xmalloc(sizeof(struct line));
		line->text = strbuf_detach(&sb, NULL);
		if (p) {
			line->next = p->next;
			p->next = line;
		} else {
			line->next = NULL;
			lines = line;
		}
		p = line;
	}

	lines = llist_mergesort(lines, get_next, set_next, compare_strings);

	while (lines) {
		printf("%s", lines->text);
		lines = lines->next;
	}
	return 0;
}