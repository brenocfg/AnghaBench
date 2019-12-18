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
typedef  int /*<<< orphan*/  secp256k1_scratch ;
typedef  int /*<<< orphan*/  secp256k1_callback ;

/* Variables and functions */
 int /*<<< orphan*/  STRAUSS_SCRATCH_OBJECTS ; 
 size_t secp256k1_scratch_max_allocation (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t secp256k1_strauss_scratch_size (int) ; 

__attribute__((used)) static size_t secp256k1_strauss_max_points(const secp256k1_callback* error_callback, secp256k1_scratch *scratch) {
    return secp256k1_scratch_max_allocation(error_callback, scratch, STRAUSS_SCRATCH_OBJECTS) / secp256k1_strauss_scratch_size(1);
}