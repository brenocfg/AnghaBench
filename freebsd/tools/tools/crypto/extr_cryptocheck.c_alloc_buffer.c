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
 char* malloc (size_t) ; 
 char rdigit () ; 

__attribute__((used)) static char *
alloc_buffer(size_t len)
{
	char *buf;
	size_t i;

	buf = malloc(len);
	for (i = 0; i < len; i++)
		buf[i] = rdigit();
	return (buf);
}