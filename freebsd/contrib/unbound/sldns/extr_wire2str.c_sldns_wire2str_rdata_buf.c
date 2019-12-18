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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int sldns_wire2str_rdata_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sldns_wire2str_rdata_buf(uint8_t* rdata, size_t rdata_len, char* str,
	size_t str_len, uint16_t rrtype)
{
	/* use arguments as temporary variables */
	return sldns_wire2str_rdata_scan(&rdata, &rdata_len, &str, &str_len,
		rrtype, NULL, 0);
}