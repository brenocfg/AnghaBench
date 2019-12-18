#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_local_inits_st {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 struct thread_local_inits_st* CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,struct thread_local_inits_st*) ; 
 int /*<<< orphan*/  OPENSSL_free (struct thread_local_inits_st*) ; 
 struct thread_local_inits_st* OPENSSL_zalloc (int) ; 
 TYPE_1__ destructor_key ; 

__attribute__((used)) static struct thread_local_inits_st *ossl_init_get_thread_local(int alloc)
{
    struct thread_local_inits_st *local =
        CRYPTO_THREAD_get_local(&destructor_key.value);

    if (alloc) {
        if (local == NULL
            && (local = OPENSSL_zalloc(sizeof(*local))) != NULL
            && !CRYPTO_THREAD_set_local(&destructor_key.value, local)) {
            OPENSSL_free(local);
            return NULL;
        }
    } else {
        CRYPTO_THREAD_set_local(&destructor_key.value, NULL);
    }

    return local;
}