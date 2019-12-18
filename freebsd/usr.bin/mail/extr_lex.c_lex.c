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
struct cmd {int /*<<< orphan*/ * c_name; } ;

/* Variables and functions */
 struct cmd* cmdtab ; 
 scalar_t__ isprefix (char*,int /*<<< orphan*/ *) ; 

const struct cmd *
lex(char word[])
{
	const struct cmd *cp;

	/*
	 * ignore trailing chars after `#'
	 *
	 * lines with beginning `#' are comments
	 * spaces before `#' are ignored in execute()
	 */

	if (*word == '#')
	    *(word+1) = '\0';


	for (cp = &cmdtab[0]; cp->c_name != NULL; cp++)
		if (isprefix(word, cp->c_name))
			return (cp);
	return (NULL);
}