#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_short ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {size_t secretsize; int /*<<< orphan*/  lifetime; int /*<<< orphan*/ * keyacclist; int /*<<< orphan*/ * secret; void* type; void* flags; int /*<<< orphan*/  keyid; } ;
typedef  TYPE_1__ symkey ;
typedef  int /*<<< orphan*/  keyid_t ;
struct TYPE_10__ {int /*<<< orphan*/  f; } ;
typedef  int /*<<< orphan*/  KeyAccT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ENSURE (int /*<<< orphan*/ ) ; 
 size_t KEYHASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_SLIST (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_TAIL_DLIST (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__) ; 
 int /*<<< orphan*/  UNLINK_HEAD_SLIST (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_moremem (int) ; 
 int /*<<< orphan*/  authfreekeys ; 
 int authnumfreekeys ; 
 int /*<<< orphan*/  authnumkeys ; 
 int /*<<< orphan*/  hlink ; 
 TYPE_1__** key_hash ; 
 int /*<<< orphan*/  key_listhead ; 
 TYPE_2__ llink ; 

__attribute__((used)) static void
allocsymkey(
	keyid_t		id,
	u_short		flags,
	u_short		type,
	u_long		lifetime,
	size_t		secretsize,
	u_char *	secret,
	KeyAccT *	ka
	)
{
	symkey *	sk;
	symkey **	bucket;

	bucket = &key_hash[KEYHASH(id)];


	if (authnumfreekeys < 1)
		auth_moremem(-1);
	UNLINK_HEAD_SLIST(sk, authfreekeys, llink.f);
	DEBUG_ENSURE(sk != NULL);
	sk->keyid = id;
	sk->flags = flags;
	sk->type = type;
	sk->secretsize = secretsize;
	sk->secret = secret;
	sk->keyacclist = ka;
	sk->lifetime = lifetime;
	LINK_SLIST(*bucket, sk, hlink);
	LINK_TAIL_DLIST(key_listhead, sk, llink);
	authnumfreekeys--;
	authnumkeys++;
}