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
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  cleanup_nonce; int /*<<< orphan*/  get_nonce; int /*<<< orphan*/  cleanup_entropy; int /*<<< orphan*/  get_entropy; int /*<<< orphan*/ * parent; } ;
typedef  int /*<<< orphan*/  RAND_DRBG_get_nonce_fn ;
typedef  int /*<<< orphan*/  RAND_DRBG_get_entropy_fn ;
typedef  int /*<<< orphan*/  RAND_DRBG_cleanup_nonce_fn ;
typedef  int /*<<< orphan*/  RAND_DRBG_cleanup_entropy_fn ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 scalar_t__ DRBG_UNINITIALISED ; 

int RAND_DRBG_set_callbacks(RAND_DRBG *drbg,
                            RAND_DRBG_get_entropy_fn get_entropy,
                            RAND_DRBG_cleanup_entropy_fn cleanup_entropy,
                            RAND_DRBG_get_nonce_fn get_nonce,
                            RAND_DRBG_cleanup_nonce_fn cleanup_nonce)
{
    if (drbg->state != DRBG_UNINITIALISED
            || drbg->parent != NULL)
        return 0;
    drbg->get_entropy = get_entropy;
    drbg->cleanup_entropy = cleanup_entropy;
    drbg->get_nonce = get_nonce;
    drbg->cleanup_nonce = cleanup_nonce;
    return 1;
}