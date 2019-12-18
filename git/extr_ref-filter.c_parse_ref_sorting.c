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
struct ref_sorting {int reverse; int version; int /*<<< orphan*/  atom; struct ref_sorting* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_sorting_atom (char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 struct ref_sorting* xcalloc (int,int) ; 

void parse_ref_sorting(struct ref_sorting **sorting_tail, const char *arg)
{
	struct ref_sorting *s;

	s = xcalloc(1, sizeof(*s));
	s->next = *sorting_tail;
	*sorting_tail = s;

	if (*arg == '-') {
		s->reverse = 1;
		arg++;
	}
	if (skip_prefix(arg, "version:", &arg) ||
	    skip_prefix(arg, "v:", &arg))
		s->version = 1;
	s->atom = parse_sorting_atom(arg);
}