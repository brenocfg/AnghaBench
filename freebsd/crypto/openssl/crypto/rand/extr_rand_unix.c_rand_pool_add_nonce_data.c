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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  RAND_POOL ;
typedef  int /*<<< orphan*/  CRYPTO_THREAD_ID ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 
 int /*<<< orphan*/  get_time_stamp () ; 
 int /*<<< orphan*/  getpid () ; 
 int rand_pool_add (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 

int rand_pool_add_nonce_data(RAND_POOL *pool)
{
    struct {
        pid_t pid;
        CRYPTO_THREAD_ID tid;
        uint64_t time;
    } data = { 0 };

    /*
     * Add process id, thread id, and a high resolution timestamp to
     * ensure that the nonce is unique with high probability for
     * different process instances.
     */
    data.pid = getpid();
    data.tid = CRYPTO_THREAD_get_current_id();
    data.time = get_time_stamp();

    return rand_pool_add(pool, (unsigned char *)&data, sizeof(data), 0);
}