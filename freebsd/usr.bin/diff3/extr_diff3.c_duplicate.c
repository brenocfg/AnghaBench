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
struct range {int to; int from; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fp ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repos (int) ; 
 int /*<<< orphan*/  skip (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
duplicate(struct range *r1, struct range *r2)
{
	int c, d;
	int nchar;
	int nline;

	if (r1->to-r1->from != r2->to-r2->from)
		return (0);
	skip(0, r1->from, NULL);
	skip(1, r2->from, NULL);
	nchar = 0;
	for (nline=0; nline < r1->to - r1->from; nline++) {
		do {
			c = getc(fp[0]);
			d = getc(fp[1]);
			if (c == -1 || d== -1)
				errx(EXIT_FAILURE, "logic error");
			nchar++;
			if (c != d) {
				repos(nchar);
				return (0);
			}
		} while (c != '\n');
	}
	repos(nchar);
	return (1);
}