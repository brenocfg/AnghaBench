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
struct TYPE_4__ {scalar_t__ alloc_size; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ secp256k1_scratch ;
typedef  int /*<<< orphan*/  secp256k1_callback ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  secp256k1_callback_call (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static void secp256k1_scratch_destroy(const secp256k1_callback* error_callback, secp256k1_scratch* scratch) {
    if (scratch != NULL) {
        VERIFY_CHECK(scratch->alloc_size == 0); /* all checkpoints should be applied */
        if (memcmp(scratch->magic, "scratch", 8) != 0) {
            secp256k1_callback_call(error_callback, "invalid scratch space");
            return;
        }
        memset(scratch->magic, 0, sizeof(scratch->magic));
        free(scratch);
    }
}