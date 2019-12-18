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
 int FALSE ; 
 int MD5authdecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  authdecryptions ; 
 int /*<<< orphan*/  authhavekey (scalar_t__) ; 
 int /*<<< orphan*/  cache_secret ; 
 int /*<<< orphan*/  cache_secretsize ; 
 int /*<<< orphan*/  cache_type ; 

int
authdecrypt(
	keyid_t		keyno,
	u_int32 *	pkt,
	size_t		length,
	size_t		size
	)
{
	/*
	 * A zero key identifier means the sender has not verified
	 * the last message was correctly authenticated.  For our
	 * purpose this is an invalid authenticator.
	 */
	authdecryptions++;
	if (0 == keyno || !authhavekey(keyno) || size < 4) {
		return FALSE;
	}

	return MD5authdecrypt(cache_type,
			      cache_secret, cache_secretsize,
			      pkt, length, size);
}