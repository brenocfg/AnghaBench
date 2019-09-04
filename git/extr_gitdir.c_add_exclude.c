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
struct exclude_list {scalar_t__ nr; struct exclude** excludes; int /*<<< orphan*/  alloc; } ;
struct exclude {char const* pattern; int patternlen; int nowildcardlen; char const* base; int baselen; unsigned int flags; int srcpos; struct exclude_list* el; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct exclude**,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int EXC_FLAG_MUSTBEDIR ; 
 int /*<<< orphan*/  FLEXPTR_ALLOC_MEM (struct exclude*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  parse_exclude_pattern (char const**,int*,unsigned int*,int*) ; 
 int /*<<< orphan*/  pattern ; 
 struct exclude* xmalloc (int) ; 

void add_exclude(const char *string, const char *base,
		 int baselen, struct exclude_list *el, int srcpos)
{
	struct exclude *x;
	int patternlen;
	unsigned flags;
	int nowildcardlen;

	parse_exclude_pattern(&string, &patternlen, &flags, &nowildcardlen);
	if (flags & EXC_FLAG_MUSTBEDIR) {
		FLEXPTR_ALLOC_MEM(x, pattern, string, patternlen);
	} else {
		x = xmalloc(sizeof(*x));
		x->pattern = string;
	}
	x->patternlen = patternlen;
	x->nowildcardlen = nowildcardlen;
	x->base = base;
	x->baselen = baselen;
	x->flags = flags;
	x->srcpos = srcpos;
	ALLOC_GROW(el->excludes, el->nr + 1, el->alloc);
	el->excludes[el->nr++] = x;
	x->el = el;
}