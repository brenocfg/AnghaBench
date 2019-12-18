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
struct input_file {int c; int /*<<< orphan*/  lineno; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int EOF ; 
 int fgetc (int /*<<< orphan*/ ) ; 

int
obtain_char(struct input_file *f)
{
	if (f->c == EOF)
		return EOF;

	f->c = fgetc(f->file);
	if (f->c == '\n')
		f->lineno++;

	return f->c;
}