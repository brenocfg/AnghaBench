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
typedef  int /*<<< orphan*/  secp256k1_context ;

/* Variables and functions */
 scalar_t__ EXPECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ checked_malloc (int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  default_error_callback ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * secp256k1_context_preallocated_create (int /*<<< orphan*/ *,unsigned int) ; 
 size_t secp256k1_context_preallocated_size (unsigned int) ; 

secp256k1_context* secp256k1_context_create(unsigned int flags) {
    size_t const prealloc_size = secp256k1_context_preallocated_size(flags);
    secp256k1_context* ctx = (secp256k1_context*)checked_malloc(&default_error_callback, prealloc_size);
    if (EXPECT(secp256k1_context_preallocated_create(ctx, flags) == NULL, 0)) {
        free(ctx);
        return NULL;
    }

    return ctx;
}