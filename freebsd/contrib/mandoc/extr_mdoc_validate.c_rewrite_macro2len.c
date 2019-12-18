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
struct roff_man {int /*<<< orphan*/  mdocmac; } ;
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;

/* Variables and functions */
 int TOKEN_NONE ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t macro2len (int) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,size_t) ; 
 int roffhash_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
rewrite_macro2len(struct roff_man *mdoc, char **arg)
{
	size_t		  width;
	enum roff_tok	  tok;

	if (*arg == NULL)
		return;
	else if ( ! strcmp(*arg, "Ds"))
		width = 6;
	else if ((tok = roffhash_find(mdoc->mdocmac, *arg, 0)) == TOKEN_NONE)
		return;
	else
		width = macro2len(tok);

	free(*arg);
	mandoc_asprintf(arg, "%zun", width);
}