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
 int /*<<< orphan*/  OPENSSL_fork_child ; 
 int /*<<< orphan*/  OPENSSL_fork_parent ; 
 int /*<<< orphan*/  OPENSSL_fork_prepare ; 
 int /*<<< orphan*/  pthread_atfork (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fork_once_func(void)
{
    pthread_atfork(OPENSSL_fork_prepare,
                   OPENSSL_fork_parent, OPENSSL_fork_child);
}