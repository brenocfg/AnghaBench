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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void
getstr(void **ptr, char *val)
{
	int *p = *ptr;
	char *c = (char *)p;
	int len = *(uint8_t *)c;

	memcpy(val, c + 1, len);
	val[len] = 0;
	c += len + 1;
	*ptr = (void *)c;
}