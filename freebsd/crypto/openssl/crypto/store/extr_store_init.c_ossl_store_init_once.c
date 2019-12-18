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
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_INIT_ONCE ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_store_init ; 
 int /*<<< orphan*/  store_init ; 

int ossl_store_init_once(void)
{
    if (!RUN_ONCE(&store_init, do_store_init)) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_INIT_ONCE, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}