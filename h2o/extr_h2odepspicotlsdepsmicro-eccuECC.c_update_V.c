#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  result_size; } ;
typedef  TYPE_1__ uECC_HashContext ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_finish (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_init (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_update (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_V(const uECC_HashContext *hash_context, uint8_t *K, uint8_t *V) {
    HMAC_init(hash_context, K);
    HMAC_update(hash_context, V, hash_context->result_size);
    HMAC_finish(hash_context, K, V);
}