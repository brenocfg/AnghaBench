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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int md5_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 

int chap_md5(u8 id, const u8 *secret, size_t secret_len, const u8 *challenge,
	      size_t challenge_len, u8 *response)
{
	const u8 *addr[3];
	size_t len[3];

	addr[0] = &id;
	len[0] = 1;
	addr[1] = secret;
	len[1] = secret_len;
	addr[2] = challenge;
	len[2] = challenge_len;
	return md5_vector(3, addr, len, response);
}