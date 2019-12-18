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
struct re_guts {int* charjump; int mlen; scalar_t__* must; } ;
struct parse {scalar_t__ error; } ;

/* Variables and functions */
 int CHAR_MAX ; 
 size_t CHAR_MIN ; 
 int NC_MAX ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static void
computejumps(struct parse *p, struct re_guts *g)
{
	int ch;
	int mindex;

	/* Avoid making errors worse */
	if (p->error != 0)
		return;

	g->charjump = (int *)malloc((NC_MAX + 1) * sizeof(int));
	if (g->charjump == NULL)	/* Not a fatal error */
		return;
	/* Adjust for signed chars, if necessary */
	g->charjump = &g->charjump[-(CHAR_MIN)];

	/* If the character does not exist in the pattern, the jump
	 * is equal to the number of characters in the pattern.
	 */
	for (ch = CHAR_MIN; ch < (CHAR_MAX + 1); ch++)
		g->charjump[ch] = g->mlen;

	/* If the character does exist, compute the jump that would
	 * take us to the last character in the pattern equal to it
	 * (notice that we match right to left, so that last character
	 * is the first one that would be matched).
	 */
	for (mindex = 0; mindex < g->mlen; mindex++)
		g->charjump[(int)g->must[mindex]] = g->mlen - mindex - 1;
}