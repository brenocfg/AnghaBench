#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* do_fgetc ) (TYPE_1__*) ;int eof; int /*<<< orphan*/  linenr; int /*<<< orphan*/  (* do_ungetc ) (int,TYPE_1__*) ;} ;

/* Variables and functions */
 int EOF ; 
 TYPE_1__* cf ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (int,TYPE_1__*) ; 

__attribute__((used)) static int get_next_char(void)
{
	int c = cf->do_fgetc(cf);

	if (c == '\r') {
		/* DOS like systems */
		c = cf->do_fgetc(cf);
		if (c != '\n') {
			if (c != EOF)
				cf->do_ungetc(c, cf);
			c = '\r';
		}
	}
	if (c == '\n')
		cf->linenr++;
	if (c == EOF) {
		cf->eof = 1;
		cf->linenr++;
		c = '\n';
	}
	return c;
}