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

/* Variables and functions */
 char CHAR_MAX ; 

__attribute__((used)) static int
get_groups(int size, char *grouping) {

	int	chars = 0;

	if (*grouping == CHAR_MAX || *grouping <= 0)	/* no grouping ? */
		return (0);

	while (size > (int)*grouping) {
		chars++;
		size -= (int)*grouping++;
		/* no more grouping ? */
		if (*grouping == CHAR_MAX)
			break;
		/* rest grouping with same value ? */
		if (*grouping == 0) {
			chars += (size - 1) / *(grouping - 1);
			break;
		}
	}
	return (chars);
}