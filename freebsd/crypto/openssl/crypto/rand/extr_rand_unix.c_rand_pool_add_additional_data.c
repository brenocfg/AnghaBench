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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  RAND_POOL ;
typedef  int /*<<< orphan*/  CRYPTO_THREAD_ID ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 
 int /*<<< orphan*/  get_timer_bits () ; 
 int openssl_get_fork_id () ; 
 int rand_pool_add (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 

int rand_pool_add_additional_data(RAND_POOL *pool)
{
    struct {
        int fork_id;
        CRYPTO_THREAD_ID tid;
        uint64_t time;
    } data = { 0 };

    /*
     * Add some noise from the thread id and a high resolution timer.
     * The fork_id adds some extra fork-safety.
     * The thread id adds a little randomness if the drbg is accessed
     * concurrently (which is the case for the <master> drbg).
     */
    data.fork_id = openssl_get_fork_id();
    data.tid = CRYPTO_THREAD_get_current_id();
    data.time = get_timer_bits();

    return rand_pool_add(pool, (unsigned char *)&data, sizeof(data), 0);
}