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

uint8_t* sldns_wirerr_get_rdata(uint8_t* rr, size_t len, size_t dname_len)
{
	if(len < dname_len+10)
		return NULL;
	return rr+dname_len+10;
}