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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ symkey ;
typedef  scalar_t__ keyid_t ;

/* Variables and functions */
 int FALSE ; 
 int KEY_TRUSTED ; 
 int TRUE ; 
 TYPE_1__* auth_findkey (scalar_t__) ; 
 int /*<<< orphan*/  authkeynotfound ; 
 int /*<<< orphan*/  authkeyuncached ; 
 int cache_flags ; 
 scalar_t__ cache_keyid ; 

int
authistrusted(
	keyid_t		id
	)
{
	symkey *	sk;

	if (id == cache_keyid)
		return !!(KEY_TRUSTED & cache_flags);

	authkeyuncached++;
	sk = auth_findkey(id);
	if (sk == NULL || !(KEY_TRUSTED & sk->flags)) {
		authkeynotfound++;
		return FALSE;
	}
	return TRUE;
}