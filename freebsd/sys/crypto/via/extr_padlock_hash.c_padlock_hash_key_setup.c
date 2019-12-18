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
struct padlock_session {int /*<<< orphan*/  ses_octx; int /*<<< orphan*/  ses_ictx; struct auth_hash* ses_axf; } ;
struct auth_hash {int blocksize; int /*<<< orphan*/  (* Update ) (int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  (* Init ) (int /*<<< orphan*/ ) ;} ;
typedef  int* caddr_t ;

/* Variables and functions */
 int HMAC_IPAD_VAL ; 
 int HMAC_OPAD_VAL ; 
 int* hmac_ipad_buffer ; 
 int* hmac_opad_buffer ; 
 int /*<<< orphan*/  padlock_free_ctx (struct auth_hash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
padlock_hash_key_setup(struct padlock_session *ses, caddr_t key, int klen)
{
	struct auth_hash *axf;
	int i;

	klen /= 8;
	axf = ses->ses_axf;

	/*
	 * Try to free contexts before using them, because
	 * padlock_hash_key_setup() can be called twice - once from
	 * padlock_newsession() and again from padlock_process().
	 */
	padlock_free_ctx(axf, ses->ses_ictx);
	padlock_free_ctx(axf, ses->ses_octx);

	for (i = 0; i < klen; i++)
		key[i] ^= HMAC_IPAD_VAL;

	axf->Init(ses->ses_ictx);
	axf->Update(ses->ses_ictx, key, klen);
	axf->Update(ses->ses_ictx, hmac_ipad_buffer, axf->blocksize - klen);

	for (i = 0; i < klen; i++)
		key[i] ^= (HMAC_IPAD_VAL ^ HMAC_OPAD_VAL);

	axf->Init(ses->ses_octx);
	axf->Update(ses->ses_octx, key, klen);
	axf->Update(ses->ses_octx, hmac_opad_buffer, axf->blocksize - klen);

	for (i = 0; i < klen; i++)
		key[i] ^= HMAC_OPAD_VAL;
}