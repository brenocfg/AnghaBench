#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_hash ) (TYPE_1__ const*,int /*<<< orphan*/  const*,unsigned int) ;} ;
typedef  TYPE_1__ uECC_HashContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__ const*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void HMAC_update(const uECC_HashContext *hash_context,
                        const uint8_t *message,
                        unsigned message_size) {
    hash_context->update_hash(hash_context, message, message_size);
}