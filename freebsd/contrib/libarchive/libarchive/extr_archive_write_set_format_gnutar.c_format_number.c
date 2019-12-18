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
typedef  int int64_t ;

/* Variables and functions */
 int format_256 (int,char*,int) ; 
 int format_octal (int,char*,int) ; 

__attribute__((used)) static int
format_number(int64_t v, char *p, int s, int maxsize)
{
	int64_t limit = ((int64_t)1 << (s*3));

	if (v < limit)
		return (format_octal(v, p, s));
	return (format_256(v, p, maxsize));
}