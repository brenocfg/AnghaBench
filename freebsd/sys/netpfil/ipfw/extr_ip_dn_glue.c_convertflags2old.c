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
 int DNOLD_HAS_PROFILE ; 
 int DNOLD_HAVE_FLOW_MASK ; 
 int DNOLD_IS_GENTLE_RED ; 
 int DNOLD_IS_RED ; 
 int DNOLD_NOERROR ; 
 int DNOLD_QSIZE_IS_BYTES ; 
 int DN_HAS_PROFILE ; 
 int DN_HAVE_MASK ; 
 int DN_IS_GENTLE_RED ; 
 int DN_IS_RED ; 
 int DN_NOERROR ; 
 int DN_QSIZE_BYTES ; 

__attribute__((used)) static int
convertflags2old(int src)
{
	int dst = 0;

	if (src & DN_HAVE_MASK)
		dst |= DNOLD_HAVE_FLOW_MASK;
	if (src & DN_IS_RED)
		dst |= DNOLD_IS_RED;
	if (src & DN_IS_GENTLE_RED)
		dst |= DNOLD_IS_GENTLE_RED;
	if (src & DN_NOERROR)
		dst |= DNOLD_NOERROR;
	if (src & DN_HAS_PROFILE)
		dst |= DNOLD_HAS_PROFILE;
	if (src & DN_QSIZE_BYTES)
		dst |= DNOLD_QSIZE_IS_BYTES;

	return dst;
}