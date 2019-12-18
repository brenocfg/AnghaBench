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
dname_lab_cmp(uint8_t* d1, int labs1, uint8_t* d2, int labs2, int* mlabs)
{
	uint8_t len1, len2;
	int atlabel = labs1;
	int lastmlabs;
	int lastdiff = 0;
	/* first skip so that we compare same label. */
	if(labs1 > labs2) {
		while(atlabel > labs2) {
			len1 = *d1++;
			d1 += len1;
			atlabel--;
		}
		log_assert(atlabel == labs2);
	} else if(labs1 < labs2) {
		atlabel = labs2;
		while(atlabel > labs1) {
			len2 = *d2++;
			d2 += len2;
			atlabel--;
		}
		log_assert(atlabel == labs1);
	}
	lastmlabs = atlabel+1;
	/* now at same label in d1 and d2, atlabel */
	/* www.example.com.                  */
	/* 4   3       2  1   atlabel number */
	/* repeat until at root label (which is always the same) */
	while(atlabel > 1) {
		len1 = *d1++;
		len2 = *d2++;
		if(len1 != len2) {
			log_assert(len1 != 0 && len2 != 0);
			if(len1<len2)
				lastdiff = -1;
			else	lastdiff = 1;
			lastmlabs = atlabel;
			d1 += len1;
			d2 += len2;
		} else {
			/* memlowercmp is inlined here; or just like
			 * if((c=memlowercmp(d1, d2, len1)) != 0) { 
			 *	lastdiff = c;
			 *	lastmlabs = atlabel; } apart from d1++,d2++ */
			while(len1) {
				if(*d1 != *d2 && tolower((unsigned char)*d1) 
					!= tolower((unsigned char)*d2)) {
					if(tolower((unsigned char)*d1) < 
						tolower((unsigned char)*d2)) {
						lastdiff = -1;
						lastmlabs = atlabel;
						d1 += len1;
						d2 += len1;
						break;
					}
					lastdiff = 1;
					lastmlabs = atlabel;
					d1 += len1;
					d2 += len1;
					break; /* out of memlowercmp */
				}
				d1++;
				d2++;
				len1--;
			}
		}
		atlabel--;
	}
	/* last difference atlabel number, so number of labels matching,
	 * at the right side, is one less. */
	*mlabs = lastmlabs-1;
	if(lastdiff == 0) {
		/* all labels compared were equal, check if one has more
		 * labels, so that example.com. > com. */
		if(labs1 > labs2)
			return 1;
		else if(labs1 < labs2)
			return -1;
	}
	return lastdiff;
}