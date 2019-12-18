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
typedef  int uint16_t ;
typedef  int u_int ;
struct cputab {int version; int /*<<< orphan*/  features2; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_features ; 
 int /*<<< orphan*/  cpu_features2 ; 
 struct cputab const* cput ; 
 int mfpvr () ; 
 struct cputab* models ; 

void
cpu_feature_setup()
{
	u_int		pvr;
	uint16_t	vers;
	const struct	cputab *cp;

	pvr = mfpvr();
	vers = pvr >> 16;
	for (cp = models; cp->version != 0; cp++) {
		if (cp->version == vers)
			break;
	}

	cput = cp;
	cpu_features |= cp->features;
	cpu_features2 |= cp->features2;
}