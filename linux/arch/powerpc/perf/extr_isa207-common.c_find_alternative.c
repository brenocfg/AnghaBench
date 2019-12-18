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
typedef  unsigned int const u64 ;

/* Variables and functions */
 int MAX_ALT ; 

__attribute__((used)) static int find_alternative(u64 event, const unsigned int ev_alt[][MAX_ALT], int size)
{
	int i, j;

	for (i = 0; i < size; ++i) {
		if (event < ev_alt[i][0])
			break;

		for (j = 0; j < MAX_ALT && ev_alt[i][j]; ++j)
			if (event == ev_alt[i][j])
				return i;
	}

	return -1;
}