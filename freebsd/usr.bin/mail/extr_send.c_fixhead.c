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
struct name {int n_type; int /*<<< orphan*/  n_name; struct name* n_flink; } ;
struct header {int /*<<< orphan*/ * h_bcc; int /*<<< orphan*/ * h_cc; int /*<<< orphan*/ * h_to; } ;

/* Variables and functions */
 int GBCC ; 
 int GCC ; 
 int GDEL ; 
 int GMASK ; 
 int GTO ; 
 void* cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nalloc (int /*<<< orphan*/ ,int) ; 

void
fixhead(struct header *hp, struct name *tolist)
{
	struct name *np;

	hp->h_to = NULL;
	hp->h_cc = NULL;
	hp->h_bcc = NULL;
	for (np = tolist; np != NULL; np = np->n_flink) {
		/* Don't copy deleted addresses to the header */
		if (np->n_type & GDEL)
			continue;
		if ((np->n_type & GMASK) == GTO)
			hp->h_to =
			    cat(hp->h_to, nalloc(np->n_name, np->n_type));
		else if ((np->n_type & GMASK) == GCC)
			hp->h_cc =
			    cat(hp->h_cc, nalloc(np->n_name, np->n_type));
		else if ((np->n_type & GMASK) == GBCC)
			hp->h_bcc =
			    cat(hp->h_bcc, nalloc(np->n_name, np->n_type));
	}
}