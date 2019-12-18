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

/* Variables and functions */
#define  QUOTE_NONE 132 
#define  QUOTE_PERL 131 
#define  QUOTE_PYTHON 130 
#define  QUOTE_SHELL 129 
#define  QUOTE_TCL 128 
 int /*<<< orphan*/  perl_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  python_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  sq_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  tcl_quote_buf (struct strbuf*,char const*) ; 

__attribute__((used)) static void quote_formatting(struct strbuf *s, const char *str, int quote_style)
{
	switch (quote_style) {
	case QUOTE_NONE:
		strbuf_addstr(s, str);
		break;
	case QUOTE_SHELL:
		sq_quote_buf(s, str);
		break;
	case QUOTE_PERL:
		perl_quote_buf(s, str);
		break;
	case QUOTE_PYTHON:
		python_quote_buf(s, str);
		break;
	case QUOTE_TCL:
		tcl_quote_buf(s, str);
		break;
	}
}