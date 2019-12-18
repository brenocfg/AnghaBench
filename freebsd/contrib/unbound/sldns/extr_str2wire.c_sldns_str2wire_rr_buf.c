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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int sldns_str2wire_rr_buf_internal (char const*,int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

int sldns_str2wire_rr_buf(const char* str, uint8_t* rr, size_t* len,
	size_t* dname_len, uint32_t default_ttl, uint8_t* origin,
	size_t origin_len, uint8_t* prev, size_t prev_len)
{
	return sldns_str2wire_rr_buf_internal(str, rr, len, dname_len,
		default_ttl, origin, origin_len, prev, prev_len, 0);
}