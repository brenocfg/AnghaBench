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
struct sline {unsigned long flag; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long find_next(struct sline *sline,
			       unsigned long mark,
			       unsigned long i,
			       unsigned long cnt,
			       int look_for_uninteresting)
{
	/* We have examined up to i-1 and are about to look at i.
	 * Find next interesting or uninteresting line.  Here,
	 * "interesting" does not mean interesting(), but marked by
	 * the give_context() function below (i.e. it includes context
	 * lines that are not interesting to interesting() function
	 * that are surrounded by interesting() ones.
	 */
	while (i <= cnt)
		if (look_for_uninteresting
		    ? !(sline[i].flag & mark)
		    : (sline[i].flag & mark))
			return i;
		else
			i++;
	return i;
}