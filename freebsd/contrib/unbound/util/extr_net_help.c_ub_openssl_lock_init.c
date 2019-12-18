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
typedef  int /*<<< orphan*/  lock_basic_type ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREADID_set_callback (int /*<<< orphan*/ *) ; 
 int CRYPTO_num_locks () ; 
 int /*<<< orphan*/  CRYPTO_set_id_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_init (int /*<<< orphan*/ *) ; 
 scalar_t__ reallocarray (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  ub_crypto_id_cb ; 
 int /*<<< orphan*/  ub_crypto_lock_cb ; 
 int /*<<< orphan*/ * ub_openssl_locks ; 

int ub_openssl_lock_init(void)
{
#if defined(HAVE_SSL) && defined(OPENSSL_THREADS) && !defined(THREADS_DISABLED) && defined(CRYPTO_LOCK) && OPENSSL_VERSION_NUMBER < 0x10100000L
	int i;
	ub_openssl_locks = (lock_basic_type*)reallocarray(
		NULL, (size_t)CRYPTO_num_locks(), sizeof(lock_basic_type));
	if(!ub_openssl_locks)
		return 0;
	for(i=0; i<CRYPTO_num_locks(); i++) {
		lock_basic_init(&ub_openssl_locks[i]);
	}
#  ifdef HAVE_CRYPTO_THREADID_SET_CALLBACK
	CRYPTO_THREADID_set_callback(&ub_crypto_id_cb);
#  else
	CRYPTO_set_id_callback(&ub_crypto_id_cb);
#  endif
	CRYPTO_set_locking_callback(&ub_crypto_lock_cb);
#endif /* OPENSSL_THREADS */
	return 1;
}