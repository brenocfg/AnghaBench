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
struct strbuf {int /*<<< orphan*/  buf; } ;
typedef  int (* config_fn_t ) (int /*<<< orphan*/ ,char*,void*) ;
struct TYPE_2__ {int /*<<< orphan*/  linenr; scalar_t__ eof; } ;

/* Variables and functions */
 TYPE_1__* cf ; 
 int get_next_char () ; 
 int /*<<< orphan*/  iskeychar (int) ; 
 char* parse_value () ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tolower (int) ; 

__attribute__((used)) static int get_value(config_fn_t fn, void *data, struct strbuf *name)
{
	int c;
	char *value;
	int ret;

	/* Get the full name */
	for (;;) {
		c = get_next_char();
		if (cf->eof)
			break;
		if (!iskeychar(c))
			break;
		strbuf_addch(name, tolower(c));
	}

	while (c == ' ' || c == '\t')
		c = get_next_char();

	value = NULL;
	if (c != '\n') {
		if (c != '=')
			return -1;
		value = parse_value();
		if (!value)
			return -1;
	}
	/*
	 * We already consumed the \n, but we need linenr to point to
	 * the line we just parsed during the call to fn to get
	 * accurate line number in error messages.
	 */
	cf->linenr--;
	ret = fn(name->buf, value, data);
	if (ret >= 0)
		cf->linenr++;
	return ret;
}