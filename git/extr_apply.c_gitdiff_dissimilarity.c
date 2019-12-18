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
struct patch {unsigned long score; } ;
struct gitdiff_data {int dummy; } ;

/* Variables and functions */
 unsigned long strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gitdiff_dissimilarity(struct gitdiff_data *state,
				 const char *line,
				 struct patch *patch)
{
	unsigned long val = strtoul(line, NULL, 10);
	if (val <= 100)
		patch->score = val;
	return 0;
}