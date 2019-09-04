#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** keys; } ;
struct TYPE_4__ {TYPE_1__ keys; } ;
typedef  int /*<<< orphan*/  RSA ;

/* Variables and functions */
 int /*<<< orphan*/  RSA_up_ref (int /*<<< orphan*/ *) ; 
 TYPE_2__ daemon_vars ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RSA *daemon_get_rsa(size_t key_index)
{
    RSA *rsa;

    pthread_mutex_lock(&daemon_vars.keys.lock);
    rsa = daemon_vars.keys.keys[key_index];
    if (rsa)
        RSA_up_ref(rsa);
    pthread_mutex_unlock(&daemon_vars.keys.lock);

    return rsa;
}