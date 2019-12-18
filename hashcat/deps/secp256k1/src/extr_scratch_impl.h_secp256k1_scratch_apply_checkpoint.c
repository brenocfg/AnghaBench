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
struct TYPE_3__ {size_t alloc_size; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ secp256k1_scratch ;
typedef  int /*<<< orphan*/  secp256k1_callback ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  secp256k1_callback_call (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static void secp256k1_scratch_apply_checkpoint(const secp256k1_callback* error_callback, secp256k1_scratch* scratch, size_t checkpoint) {
    if (memcmp(scratch->magic, "scratch", 8) != 0) {
        secp256k1_callback_call(error_callback, "invalid scratch space");
        return;
    }
    if (checkpoint > scratch->alloc_size) {
        secp256k1_callback_call(error_callback, "invalid checkpoint");
        return;
    }
    scratch->alloc_size = checkpoint;
}