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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int sldns_wire2str_dname_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sldns_wire2str_dname_buf(uint8_t* d, size_t dlen, char* s, size_t slen)
{
	/* use arguments as temporary variables */
	return sldns_wire2str_dname_scan(&d, &dlen, &s, &slen, NULL, 0);
}