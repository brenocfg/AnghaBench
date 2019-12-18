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
struct re_guts {int mlen; int* matchjump; scalar_t__* must; } ;
struct parse {scalar_t__ error; } ;

/* Variables and functions */
 void* MIN (int,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static void
computematchjumps(struct parse *p, struct re_guts *g)
{
	int mindex;		/* General "must" iterator */
	int suffix;		/* Keeps track of matching suffix */
	int ssuffix;		/* Keeps track of suffixes' suffix */
	int* pmatches;		/* pmatches[k] points to the next i
				 * such that i+1...mlen is a substring
				 * of k+1...k+mlen-i-1
				 */

	/* Avoid making errors worse */
	if (p->error != 0)
		return;

	pmatches = (int*) malloc(g->mlen * sizeof(int));
	if (pmatches == NULL) {
		g->matchjump = NULL;
		return;
	}

	g->matchjump = (int*) malloc(g->mlen * sizeof(int));
	if (g->matchjump == NULL) {	/* Not a fatal error */
		free(pmatches);
		return;
	}

	/* Set maximum possible jump for each character in the pattern */
	for (mindex = 0; mindex < g->mlen; mindex++)
		g->matchjump[mindex] = 2*g->mlen - mindex - 1;

	/* Compute pmatches[] */
	for (mindex = g->mlen - 1, suffix = g->mlen; mindex >= 0;
	    mindex--, suffix--) {
		pmatches[mindex] = suffix;

		/* If a mismatch is found, interrupting the substring,
		 * compute the matchjump for that position. If no
		 * mismatch is found, then a text substring mismatched
		 * against the suffix will also mismatch against the
		 * substring.
		 */
		while (suffix < g->mlen
		    && g->must[mindex] != g->must[suffix]) {
			g->matchjump[suffix] = MIN(g->matchjump[suffix],
			    g->mlen - mindex - 1);
			suffix = pmatches[suffix];
		}
	}

	/* Compute the matchjump up to the last substring found to jump
	 * to the beginning of the largest must pattern prefix matching
	 * it's own suffix.
	 */
	for (mindex = 0; mindex <= suffix; mindex++)
		g->matchjump[mindex] = MIN(g->matchjump[mindex],
		    g->mlen + suffix - mindex);

        ssuffix = pmatches[suffix];
        while (suffix < g->mlen) {
                while (suffix <= ssuffix && suffix < g->mlen) {
                        g->matchjump[suffix] = MIN(g->matchjump[suffix],
			    g->mlen + ssuffix - suffix);
                        suffix++;
                }
		if (suffix < g->mlen)
                	ssuffix = pmatches[ssuffix];
        }

	free(pmatches);
}