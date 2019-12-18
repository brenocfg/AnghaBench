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
struct mapinfo {scalar_t__ mapoff; scalar_t__ maplen; scalar_t__ start; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  WR (scalar_t__,int) ; 
 scalar_t__ maparound (struct mapinfo*,scalar_t__) ; 

int
mapprint(struct mapinfo *mip, off_t startoff, off_t len)
{
	int n;

	while (len > 0) {
		if (startoff < mip->mapoff || startoff >= mip->mapoff +
		    (off_t)mip->maplen) {
			if (maparound(mip, startoff) != 0)
				return (1);
		}
		n = (mip->mapoff + mip->maplen) - startoff;
		if (n > len)
			n = len;
		WR(mip->start + (startoff - mip->mapoff), n);
		startoff += n;
		len -= n;
	}
	return (0);
}