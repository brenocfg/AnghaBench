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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_B ; 
 int HN_NOSPACE ; 
 int /*<<< orphan*/  humanize_number (char*,size_t,int,char*,int /*<<< orphan*/ ,int) ; 

void
format_stripe(char *buf, size_t buflen, uint8_t stripe)
{

	humanize_number(buf, buflen, (1 << stripe) * 512, "", HN_AUTOSCALE,  
	    HN_B | HN_NOSPACE);
}