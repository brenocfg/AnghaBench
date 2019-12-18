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
typedef  int hash_variant_t ;

/* Variables and functions */
#define  hash_variant_x64_128 130 
#define  hash_variant_x86_128 129 
#define  hash_variant_x86_32 128 
 int /*<<< orphan*/  not_reached () ; 

__attribute__((used)) static const char *
hash_variant_string(hash_variant_t variant) {
	switch (variant) {
	case hash_variant_x86_32: return "hash_x86_32";
	case hash_variant_x86_128: return "hash_x86_128";
	case hash_variant_x64_128: return "hash_x64_128";
	default: not_reached();
	}
}