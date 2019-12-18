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
struct roff_man {TYPE_1__* last; } ;
typedef  enum margserr { ____Placeholder_margserr } margserr ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ARGS_ALLOC ; 
 int ARGS_EOLN ; 
 int /*<<< orphan*/  DELIM_MAX ; 
 int /*<<< orphan*/  NODE_EOS ; 
 int /*<<< orphan*/  TOKEN_NONE ; 
 int /*<<< orphan*/  dword (struct roff_man*,int,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mandoc_eos (char*,int /*<<< orphan*/ ) ; 
 int mdoc_args (struct roff_man*,int,int*,char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
append_delims(struct roff_man *mdoc, int line, int *pos, char *buf)
{
	char		*p;
	int		 la;
	enum margserr	 ac;

	if (buf[*pos] == '\0')
		return;

	for (;;) {
		la = *pos;
		ac = mdoc_args(mdoc, line, pos, buf, TOKEN_NONE, &p);
		if (ac == ARGS_EOLN)
			break;
		dword(mdoc, line, la, p, DELIM_MAX, 1);

		/*
		 * If we encounter end-of-sentence symbols, then trigger
		 * the double-space.
		 *
		 * XXX: it's easy to allow this to propagate outward to
		 * the last symbol, such that `. )' will cause the
		 * correct double-spacing.  However, (1) groff isn't
		 * smart enough to do this and (2) it would require
		 * knowing which symbols break this behaviour, for
		 * example, `.  ;' shouldn't propagate the double-space.
		 */

		if (mandoc_eos(p, strlen(p)))
			mdoc->last->flags |= NODE_EOS;
		if (ac == ARGS_ALLOC)
			free(p);
	}
}