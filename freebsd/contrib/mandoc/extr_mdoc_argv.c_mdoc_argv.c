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
struct roff_man {int dummy; } ;
struct mdoc_argv {size_t arg; int line; int pos; int /*<<< orphan*/ * value; scalar_t__ sz; } ;
struct mdoc_arg {int argc; struct mdoc_argv* argv; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;
typedef  enum mdocargt { ____Placeholder_mdocargt } mdocargt ;
struct TYPE_2__ {int* argvs; } ;

/* Variables and functions */
#define  ARGV_MULTI 130 
#define  ARGV_NONE 129 
#define  ARGV_SINGLE 128 
 size_t MDOC_ARG_MAX ; 
 int MDOC_Dd ; 
 int MDOC_MAX ; 
 int /*<<< orphan*/  argv_multi (struct roff_man*,int,struct mdoc_argv*,int*,char*) ; 
 int /*<<< orphan*/  argv_single (struct roff_man*,int,struct mdoc_argv*,int*,char*) ; 
 int* argvflags ; 
 int /*<<< orphan*/  assert (int) ; 
 struct mdoc_arg* mandoc_calloc (int,int) ; 
 struct mdoc_argv* mandoc_reallocarray (struct mdoc_argv*,int,int) ; 
 int /*<<< orphan*/ * mdoc_argnames ; 
 TYPE_1__* mdocargs ; 
 int /*<<< orphan*/  memcpy (struct mdoc_argv*,struct mdoc_argv*,int) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

void
mdoc_argv(struct roff_man *mdoc, int line, enum roff_tok tok,
	struct mdoc_arg **reta, int *pos, char *buf)
{
	struct mdoc_argv	  tmpv;
	struct mdoc_argv	**retv;
	const enum mdocargt	 *argtable;
	char			 *argname;
	int			  ipos, retc;
	char			  savechar;

	*reta = NULL;

	/* Which flags does this macro support? */

	assert(tok >= MDOC_Dd && tok < MDOC_MAX);
	argtable = mdocargs[tok - MDOC_Dd].argvs;
	if (argtable == NULL)
		return;

	/* Loop over the flags on the input line. */

	ipos = *pos;
	while (buf[ipos] == '-') {

		/* Seek to the first unescaped space. */

		for (argname = buf + ++ipos; buf[ipos] != '\0'; ipos++)
			if (buf[ipos] == ' ' && buf[ipos - 1] != '\\')
				break;

		/*
		 * We want to nil-terminate the word to look it up.
		 * But we may not have a flag, in which case we need
		 * to restore the line as-is.  So keep around the
		 * stray byte, which we'll reset upon exiting.
		 */

		if ((savechar = buf[ipos]) != '\0')
			buf[ipos++] = '\0';

		/*
		 * Now look up the word as a flag.  Use temporary
		 * storage that we'll copy into the node's flags.
		 */

		while ((tmpv.arg = *argtable++) != MDOC_ARG_MAX)
			if ( ! strcmp(argname, mdoc_argnames[tmpv.arg]))
				break;

		/* If it isn't a flag, restore the saved byte. */

		if (tmpv.arg == MDOC_ARG_MAX) {
			if (savechar != '\0')
				buf[ipos - 1] = savechar;
			break;
		}

		/* Read to the next word (the first argument). */

		while (buf[ipos] == ' ')
			ipos++;

		/* Parse the arguments of the flag. */

		tmpv.line  = line;
		tmpv.pos   = *pos;
		tmpv.sz    = 0;
		tmpv.value = NULL;

		switch (argvflags[tmpv.arg]) {
		case ARGV_SINGLE:
			argv_single(mdoc, line, &tmpv, &ipos, buf);
			break;
		case ARGV_MULTI:
			argv_multi(mdoc, line, &tmpv, &ipos, buf);
			break;
		case ARGV_NONE:
			break;
		}

		/* Append to the return values. */

		if (*reta == NULL)
			*reta = mandoc_calloc(1, sizeof(**reta));

		retc = ++(*reta)->argc;
		retv = &(*reta)->argv;
		*retv = mandoc_reallocarray(*retv, retc, sizeof(**retv));
		memcpy(*retv + retc - 1, &tmpv, sizeof(**retv));

		/* Prepare for parsing the next flag. */

		*pos = ipos;
		argtable = mdocargs[tok - MDOC_Dd].argvs;
	}
}