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
struct TYPE_2__ {int sane; } ;

/* Variables and functions */
 TYPE_1__ destructor_key ; 
 int /*<<< orphan*/  ossl_init_get_thread_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_init_thread_stop (int /*<<< orphan*/ ) ; 

void OPENSSL_thread_stop(void)
{
    if (destructor_key.sane != -1)
        ossl_init_thread_stop(ossl_init_get_thread_local(0));
}