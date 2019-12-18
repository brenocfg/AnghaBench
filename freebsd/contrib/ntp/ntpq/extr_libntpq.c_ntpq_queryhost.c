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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int doquery (unsigned short,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t*,char const**) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ numhosts ; 

int ntpq_queryhost(unsigned short VARSET, unsigned short association, char *resultbuf, int maxlen)
{
	const char *datap;
	int res;
	size_t	dsize;
	u_short	rstatus;
	
	if ( numhosts > 0 )
		res = doquery(VARSET,association,0,0, (char *)0, &rstatus, &dsize, &datap);
	else
		return 0;
	
	if ( ( res != 0) || ( dsize == 0 ) ) /* no data */
		return 0;
	
	if ( dsize > maxlen) 
		dsize = maxlen;
	
	
	/* fill result resultbuf */
	memcpy(resultbuf, datap, dsize);
	
	return dsize;
}