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
struct input_file {int lineno; int /*<<< orphan*/  name; scalar_t__ c; int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  emit_synchline () ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
set_input(struct input_file *f, FILE *real, const char *name)
{
	f->file = real;
	f->lineno = 1;
	f->c = 0;
	f->name = xstrdup(name);
	emit_synchline();
}