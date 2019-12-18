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
struct thread_local_inits_st {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_init_thread_stop (struct thread_local_inits_st*) ; 

__attribute__((used)) static void ossl_init_thread_destructor(void *local)
{
    ossl_init_thread_stop((struct thread_local_inits_st *)local);
}