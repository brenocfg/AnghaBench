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
typedef  int u8 ;
typedef  int /*<<< orphan*/  nsid ;

/* Variables and functions */
 int SHA1_MAC_LEN ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  sha1_vector (int,int const**,size_t*,int*) ; 

void uuid_gen_mac_addr(const u8 *mac_addr, u8 *uuid)
{
	const u8 *addr[2];
	size_t len[2];
	u8 hash[SHA1_MAC_LEN];
	u8 nsid[16] = {
		0x52, 0x64, 0x80, 0xf8,
		0xc9, 0x9b,
		0x4b, 0xe5,
		0xa6, 0x55,
		0x58, 0xed, 0x5f, 0x5d, 0x60, 0x84
	};

	addr[0] = nsid;
	len[0] = sizeof(nsid);
	addr[1] = mac_addr;
	len[1] = 6;
	sha1_vector(2, addr, len, hash);
	os_memcpy(uuid, hash, 16);

	/* Version: 5 = named-based version using SHA-1 */
	uuid[6] = (5 << 4) | (uuid[6] & 0x0f);

	/* Variant specified in RFC 4122 */
	uuid[8] = 0x80 | (uuid[8] & 0x3f);
}