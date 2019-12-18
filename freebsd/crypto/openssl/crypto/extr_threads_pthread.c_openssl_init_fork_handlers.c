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
 int /*<<< orphan*/  fork_once_control ; 
 int /*<<< orphan*/  fork_once_func ; 
 scalar_t__ pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int openssl_init_fork_handlers(void)
{
# ifdef OPENSSL_SYS_UNIX
    if (pthread_once(&fork_once_control, fork_once_func) == 0)
        return 1;
# endif
    return 0;
}