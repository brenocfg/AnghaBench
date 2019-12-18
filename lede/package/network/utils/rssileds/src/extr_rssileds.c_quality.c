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
struct iwinfo_ops {scalar_t__ (* quality ) (char const*,int*) ;scalar_t__ (* quality_max ) (char const*,int*) ;} ;

/* Variables and functions */
 int qual_max ; 
 scalar_t__ stub1 (char const*,int*) ; 
 scalar_t__ stub2 (char const*,int*) ; 

int quality(const struct iwinfo_ops *iw, const char *ifname)
{
	int qual;

	if ( ! iw ) return -1;

	if (qual_max < 1)
		if (iw->quality_max(ifname, &qual_max))
			return -1;

	if (iw->quality(ifname, &qual))
		return -1;

	return ( qual * 100 ) / qual_max ;
}