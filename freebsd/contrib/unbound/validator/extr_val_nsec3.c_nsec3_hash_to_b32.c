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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,size_t) ; 
 int sldns_b32_ntop_extended_hex (scalar_t__*,size_t,char*,size_t) ; 

size_t nsec3_hash_to_b32(uint8_t* hash, size_t hashlen, uint8_t* zone,
	size_t zonelen, uint8_t* buf, size_t max)
{
	/* write b32 of name, leave one for length */
	int ret;
	if(max < hashlen*2+1) /* quick approx of b32, as if hexb16 */
		return 0;
	ret = sldns_b32_ntop_extended_hex(hash, hashlen, (char*)buf+1, max-1);
	if(ret < 1) 
		return 0;
	buf[0] = (uint8_t)ret; /* length of b32 label */
	ret++;
	if(max - ret < zonelen)
		return 0;
	memmove(buf+ret, zone, zonelen);
	return zonelen+(size_t)ret;
}