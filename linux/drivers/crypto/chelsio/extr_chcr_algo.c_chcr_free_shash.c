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
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 

__attribute__((used)) static inline void chcr_free_shash(struct crypto_shash *base_hash)
{
		crypto_free_shash(base_hash);
}