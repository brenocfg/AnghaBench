#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int /*<<< orphan*/  keyacclist; } ;
typedef  TYPE_1__ symkey ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  scalar_t__ keyid_t ;

/* Variables and functions */
 int FALSE ; 
 int KEY_TRUSTED ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* auth_findkey (scalar_t__) ; 
 int /*<<< orphan*/  authkeynotfound ; 
 int /*<<< orphan*/  authkeyuncached ; 
 int cache_flags ; 
 int /*<<< orphan*/  cache_keyacclist ; 
 scalar_t__ cache_keyid ; 
 scalar_t__ keyacc_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
 authistrustedip(
 	keyid_t		keyno,
	sockaddr_u *	sau
	)
{
	symkey *	sk;

	if (keyno == cache_keyid) {
		return (KEY_TRUSTED & cache_flags) &&
		    keyacc_contains(cache_keyacclist, sau, TRUE);
	}

	if (NULL != (sk = auth_findkey(keyno))) {
		authkeyuncached++;
		return (KEY_TRUSTED & sk->flags) &&
		    keyacc_contains(sk->keyacclist, sau, TRUE);
	}
	
	authkeynotfound++;
	return FALSE;    
}