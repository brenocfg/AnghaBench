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
typedef  int /*<<< orphan*/  u_int32 ;
typedef  scalar_t__ keyid_t ;

/* Variables and functions */
 size_t MD5authencrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  authencryptions ; 
 int /*<<< orphan*/  authhavekey (scalar_t__) ; 
 int /*<<< orphan*/  cache_secret ; 
 int /*<<< orphan*/  cache_secretsize ; 
 int /*<<< orphan*/  cache_type ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 

size_t
authencrypt(
	keyid_t		keyno,
	u_int32 *	pkt,
	size_t		length
	)
{
	/*
	 * A zero key identifier means the sender has not verified
	 * the last message was correctly authenticated. The MAC
	 * consists of a single word with value zero.
	 */
	authencryptions++;
	pkt[length / 4] = htonl(keyno);
	if (0 == keyno) {
		return 4;
	}
	if (!authhavekey(keyno)) {
		return 0;
	}

	return MD5authencrypt(cache_type,
			      cache_secret, cache_secretsize,
			      pkt, length);
}