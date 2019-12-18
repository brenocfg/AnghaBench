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
struct parse {char* next; char* end; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  p_bracket (struct parse*) ; 

__attribute__((used)) static void
nonnewline(struct parse *p)
{
	char *oldnext = p->next;
	char *oldend = p->end;
	char bracket[4];

	p->next = bracket;
	p->end = bracket+3;
	bracket[0] = '^';
	bracket[1] = '\n';
	bracket[2] = ']';
	bracket[3] = '\0';
	p_bracket(p);
	assert(p->next == bracket+3);
	p->next = oldnext;
	p->end = oldend;
}