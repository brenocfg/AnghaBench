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
typedef  char uchar ;

/* Variables and functions */
 scalar_t__ domalloc (int) ; 
 scalar_t__ strncpy (char*,char*,int) ; 

uchar *
newstring(uchar *s, int l, int o)
{
	uchar *ns = (uchar *)domalloc(l+o+1);

	ns[l+o] = '\0';
	return (uchar*)strncpy((char*)ns+o, (char*)s, l) - o;
}