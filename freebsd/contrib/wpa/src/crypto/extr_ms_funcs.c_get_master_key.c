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
typedef  int /*<<< orphan*/  magic1 ;

/* Variables and functions */
 int SHA1_MAC_LEN ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 
 scalar_t__ sha1_vector (int,unsigned char const**,size_t const*,int*) ; 

int get_master_key(const u8 *password_hash_hash, const u8 *nt_response,
		   u8 *master_key)
{
	static const u8 magic1[27] = {
		0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x74,
		0x68, 0x65, 0x20, 0x4d, 0x50, 0x50, 0x45, 0x20, 0x4d,
		0x61, 0x73, 0x74, 0x65, 0x72, 0x20, 0x4b, 0x65, 0x79
	};
	const unsigned char *addr[3];
	const size_t len[3] = { 16, 24, sizeof(magic1) };
	u8 hash[SHA1_MAC_LEN];

	addr[0] = password_hash_hash;
	addr[1] = nt_response;
	addr[2] = magic1;

	if (sha1_vector(3, addr, len, hash))
		return -1;
	os_memcpy(master_key, hash, 16);
	return 0;
}