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
typedef  int u_int64_t ;
typedef  void* u_int32_t ;
struct fcrypt {int dummy; } ;
struct enc_xform {int dummy; } ;
struct csession {int keylen; int mackeylen; struct auth_hash* thash; struct enc_xform* txform; void* mac; void* cipher; int /*<<< orphan*/  cses; void* mackey; void* key; int /*<<< orphan*/  lock; } ;
struct auth_hash {int dummy; } ;
typedef  int /*<<< orphan*/  crypto_session_t ;
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_XDATA ; 
 int M_ZERO ; 
 int /*<<< orphan*/  cseadd (struct fcrypt*,struct csession*) ; 
 struct csession* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

struct csession *
csecreate(struct fcrypt *fcr, crypto_session_t cses, caddr_t key, u_int64_t keylen,
    caddr_t mackey, u_int64_t mackeylen, u_int32_t cipher, u_int32_t mac,
    struct enc_xform *txform, struct auth_hash *thash)
{
	struct csession *cse;

	cse = malloc(sizeof(struct csession), M_XDATA, M_NOWAIT | M_ZERO);
	if (cse == NULL)
		return NULL;
	mtx_init(&cse->lock, "cryptodev", "crypto session lock", MTX_DEF);
	cse->key = key;
	cse->keylen = keylen/8;
	cse->mackey = mackey;
	cse->mackeylen = mackeylen/8;
	cse->cses = cses;
	cse->cipher = cipher;
	cse->mac = mac;
	cse->txform = txform;
	cse->thash = thash;
	cseadd(fcr, cse);
	return (cse);
}