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

/* Variables and functions */
 int CRYPTO_LOCK ; 
 int CRYPTO_UNLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mutexes ; 
 int /*<<< orphan*/  pthread_mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (scalar_t__) ; 

__attribute__((used)) static void lock_callback(int mode, int n, const char *file, int line)
{
    if ((mode & CRYPTO_LOCK) != 0) {
        pthread_mutex_lock(mutexes + n);
    } else if ((mode & CRYPTO_UNLOCK) != 0) {
        pthread_mutex_unlock(mutexes + n);
    } else {
        assert(!"unexpected mode");
    }
}