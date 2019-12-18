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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  hash_variant_t ;

/* Variables and functions */
 int KEY_SIZE ; 
 int MAX_ALIGN ; 
 int /*<<< orphan*/  hash_variant_verify_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hash_variant_verify(hash_variant_t variant) {
#define MAX_ALIGN	16
	uint8_t key[KEY_SIZE + (MAX_ALIGN - 1)];
	unsigned i;

	for (i = 0; i < MAX_ALIGN; i++) {
		hash_variant_verify_key(variant, &key[i]);
	}
#undef MAX_ALIGN
}