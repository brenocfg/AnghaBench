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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int sldns_wire2str_type_print (char**,size_t*,int /*<<< orphan*/ ) ; 

int sldns_wire2str_type_buf(uint16_t rrtype, char* s, size_t slen)
{
	/* use arguments as temporary variables */
	return sldns_wire2str_type_print(&s, &slen, rrtype);
}