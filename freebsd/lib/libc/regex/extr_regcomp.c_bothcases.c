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
typedef  int /*<<< orphan*/  wint_t ;
struct parse {char* next; char* end; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 int /*<<< orphan*/  MB_LEN_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  othercase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_bracket (struct parse*) ; 
 size_t wcrtomb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bothcases(struct parse *p, wint_t ch)
{
	const char *oldnext = p->next;
	const char *oldend = p->end;
	char bracket[3 + MB_LEN_MAX];
	size_t n;
	mbstate_t mbs;

	assert(othercase(ch) != ch);	/* p_bracket() would recurse */
	p->next = bracket;
	memset(&mbs, 0, sizeof(mbs));
	n = wcrtomb(bracket, ch, &mbs);
	assert(n != (size_t)-1);
	bracket[n] = ']';
	bracket[n + 1] = '\0';
	p->end = bracket+n+1;
	p_bracket(p);
	assert(p->next == p->end);
	p->next = oldnext;
	p->end = oldend;
}