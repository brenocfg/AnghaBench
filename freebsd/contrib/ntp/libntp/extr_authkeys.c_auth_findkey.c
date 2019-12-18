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
struct savekey {scalar_t__ keyid; struct savekey* hlink; } ;
typedef  struct savekey symkey ;
typedef  scalar_t__ keyid_t ;

/* Variables and functions */
 size_t KEYHASH (scalar_t__) ; 
 struct savekey** key_hash ; 

struct savekey *
auth_findkey(
	keyid_t		id
	)
{
	symkey *	sk;

	for (sk = key_hash[KEYHASH(id)]; sk != NULL; sk = sk->hlink)
		if (id == sk->keyid)
			return sk;
	return NULL;
}