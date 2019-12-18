#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__ BN_BLINDING ;

/* Variables and functions */
 int CRYPTO_THREAD_compare_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 

int BN_BLINDING_is_current_thread(BN_BLINDING *b)
{
    return CRYPTO_THREAD_compare_id(CRYPTO_THREAD_get_current_id(), b->tid);
}