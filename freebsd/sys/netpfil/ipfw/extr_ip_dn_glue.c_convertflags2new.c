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
convertflags2new(int src)
{
	int dst = 0;

	if (src & DNOLD_HAVE_FLOW_MASK)
		dst |= DN_HAVE_MASK;
	if (src & DNOLD_QSIZE_IS_BYTES)
		dst |= DN_QSIZE_BYTES;
	if (src & DNOLD_NOERROR)
		dst |= DN_NOERROR;
	if (src & DNOLD_IS_RED)
		dst |= DN_IS_RED;
	if (src & DNOLD_IS_GENTLE_RED)
		dst |= DN_IS_GENTLE_RED;
	if (src & DNOLD_HAS_PROFILE)
		dst |= DN_HAS_PROFILE;

	return dst;
}