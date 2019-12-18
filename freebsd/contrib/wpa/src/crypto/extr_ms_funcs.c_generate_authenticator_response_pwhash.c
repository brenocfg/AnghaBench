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
typedef  int /*<<< orphan*/  magic2 ;
typedef  int /*<<< orphan*/  magic1 ;

/* Variables and functions */
 int SHA1_MAC_LEN ; 
 scalar_t__ challenge_hash (int const*,int const*,int const*,size_t,int*) ; 
 scalar_t__ hash_nt_password_hash (int const*,int*) ; 
 int sha1_vector (int,unsigned char const**,size_t const*,int*) ; 

int generate_authenticator_response_pwhash(
	const u8 *password_hash,
	const u8 *peer_challenge, const u8 *auth_challenge,
	const u8 *username, size_t username_len,
	const u8 *nt_response, u8 *response)
{
	static const u8 magic1[39] = {
		0x4D, 0x61, 0x67, 0x69, 0x63, 0x20, 0x73, 0x65, 0x72, 0x76,
		0x65, 0x72, 0x20, 0x74, 0x6F, 0x20, 0x63, 0x6C, 0x69, 0x65,
		0x6E, 0x74, 0x20, 0x73, 0x69, 0x67, 0x6E, 0x69, 0x6E, 0x67,
		0x20, 0x63, 0x6F, 0x6E, 0x73, 0x74, 0x61, 0x6E, 0x74
	};
	static const u8 magic2[41] = {
		0x50, 0x61, 0x64, 0x20, 0x74, 0x6F, 0x20, 0x6D, 0x61, 0x6B,
		0x65, 0x20, 0x69, 0x74, 0x20, 0x64, 0x6F, 0x20, 0x6D, 0x6F,
		0x72, 0x65, 0x20, 0x74, 0x68, 0x61, 0x6E, 0x20, 0x6F, 0x6E,
		0x65, 0x20, 0x69, 0x74, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6F,
		0x6E
	};

	u8 password_hash_hash[16], challenge[8];
	const unsigned char *addr1[3];
	const size_t len1[3] = { 16, 24, sizeof(magic1) };
	const unsigned char *addr2[3];
	const size_t len2[3] = { SHA1_MAC_LEN, 8, sizeof(magic2) };

	addr1[0] = password_hash_hash;
	addr1[1] = nt_response;
	addr1[2] = magic1;

	addr2[0] = response;
	addr2[1] = challenge;
	addr2[2] = magic2;

	if (hash_nt_password_hash(password_hash, password_hash_hash) ||
	    sha1_vector(3, addr1, len1, response) ||
	    challenge_hash(peer_challenge, auth_challenge, username,
			   username_len, challenge))
		return -1;
	return sha1_vector(3, addr2, len2, response);
}