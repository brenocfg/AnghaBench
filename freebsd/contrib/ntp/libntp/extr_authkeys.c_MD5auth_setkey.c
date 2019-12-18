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
typedef  scalar_t__ u_short ;
typedef  int u_char ;
struct TYPE_3__ {scalar_t__ keyid; int* secret; size_t secretsize; int /*<<< orphan*/ * keyacclist; scalar_t__ type; } ;
typedef  TYPE_1__ symkey ;
typedef  scalar_t__ keyid_t ;
typedef  int /*<<< orphan*/  KeyAccT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ENSURE (int) ; 
 int USHRT_MAX ; 
 int /*<<< orphan*/  allocsymkey (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,size_t,int*,int /*<<< orphan*/ *) ; 
 TYPE_1__* auth_findkey (scalar_t__) ; 
 int /*<<< orphan*/  authcache_flush_id (scalar_t__) ; 
 int debug ; 
 void* emalloc (size_t) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  keyacc_all_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

void
MD5auth_setkey(
	keyid_t keyno,
	int	keytype,
	const u_char *key,
	size_t secretsize,
	KeyAccT *ka
	)
{
	symkey *	sk;
	u_char *	secret;
	
	DEBUG_ENSURE(keytype <= USHRT_MAX);
	DEBUG_ENSURE(secretsize < 4 * 1024);
	/*
	 * See if we already have the key.  If so just stick in the
	 * new value.
	 */
	sk = auth_findkey(keyno);
	if (sk != NULL && keyno == sk->keyid) {
			/* TALOS-CAN-0054: make sure we have a new buffer! */
		if (NULL != sk->secret) {
			memset(sk->secret, 0, sk->secretsize);
			free(sk->secret);
		}
		sk->secret = emalloc(secretsize + 1);
		sk->type = (u_short)keytype;
		sk->secretsize = secretsize;
		/* make sure access lists don't leak here! */
		if (ka != sk->keyacclist) {
			keyacc_all_free(sk->keyacclist);
			sk->keyacclist = ka;
		}
#ifndef DISABLE_BUG1243_FIX
		memcpy(sk->secret, key, secretsize);
#else
		/* >MUST< use 'strncpy()' here! See above! */
		strncpy((char *)sk->secret, (const char *)key,
			secretsize);
#endif
		authcache_flush_id(keyno);
		return;
	}

	/*
	 * Need to allocate new structure.  Do it.
	 */
	secret = emalloc(secretsize + 1);
#ifndef DISABLE_BUG1243_FIX
	memcpy(secret, key, secretsize);
#else
	/* >MUST< use 'strncpy()' here! See above! */
	strncpy((char *)secret, (const char *)key, secretsize);
#endif
	allocsymkey(keyno, 0, (u_short)keytype, 0,
		    secretsize, secret, ka);
#ifdef DEBUG
	if (debug >= 4) {
		size_t	j;

		printf("auth_setkey: key %d type %d len %d ", (int)keyno,
		    keytype, (int)secretsize);
		for (j = 0; j < secretsize; j++) {
			printf("%02x", secret[j]);
		}
		printf("\n");
	}	
#endif
}