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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ tolower (unsigned char) ; 

int 
query_dname_compare(register uint8_t* d1, register uint8_t* d2)
{
	register uint8_t lab1, lab2;
	log_assert(d1 && d2);
	lab1 = *d1++;
	lab2 = *d2++;
	while( lab1 != 0 || lab2 != 0 ) {
		/* compare label length */
		/* if one dname ends, it has labellength 0 */
		if(lab1 != lab2) {
			if(lab1 < lab2)
				return -1;
			return 1;
		}
		log_assert(lab1 == lab2 && lab1 != 0);
		/* compare lowercased labels. */
		while(lab1--) {
			/* compare bytes first for speed */
			if(*d1 != *d2 && 
				tolower((unsigned char)*d1) != tolower((unsigned char)*d2)) {
				if(tolower((unsigned char)*d1) < tolower((unsigned char)*d2))
					return -1;
				return 1;
			}
			d1++;
			d2++;
		}
		/* next pair of labels. */
		lab1 = *d1++;
		lab2 = *d2++;
	}
	return 0;
}