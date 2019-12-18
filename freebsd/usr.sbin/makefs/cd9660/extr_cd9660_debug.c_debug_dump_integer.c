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
 int debug_get_encoded_number (unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,char const*) ; 

void
debug_dump_integer(const char *element, char* buf, int mode)
{
	printf("<%s>%i</%s>\n", element,
	    debug_get_encoded_number((unsigned char *)buf, mode), element);
}