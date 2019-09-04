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
struct strbuf {int dummy; } ;
struct TYPE_2__ {int subsection_case_sensitive; scalar_t__ eof; } ;

/* Variables and functions */
 TYPE_1__* cf ; 
 int get_extended_base_var (struct strbuf*,int) ; 
 int get_next_char () ; 
 int /*<<< orphan*/  iskeychar (int) ; 
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tolower (int) ; 

__attribute__((used)) static int get_base_var(struct strbuf *name)
{
	cf->subsection_case_sensitive = 1;
	for (;;) {
		int c = get_next_char();
		if (cf->eof)
			return -1;
		if (c == ']')
			return 0;
		if (isspace(c))
			return get_extended_base_var(name, c);
		if (!iskeychar(c) && c != '.')
			return -1;
		strbuf_addch(name, tolower(c));
	}
}