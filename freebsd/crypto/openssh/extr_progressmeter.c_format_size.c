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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,long long,char,char*) ; 
 char* unit ; 

__attribute__((used)) static void
format_size(char *buf, int size, off_t bytes)
{
	int i;

	for (i = 0; bytes >= 10000 && unit[i] != 'T'; i++)
		bytes = (bytes + 512) / 1024;
	snprintf(buf, size, "%4lld%c%s",
	    (long long) bytes,
	    unit[i],
	    i ? "B" : " ");
}