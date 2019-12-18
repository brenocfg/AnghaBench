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
struct futex_address {int /*<<< orphan*/  fa_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  umtx_key_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
futex_address_free(struct futex_address *fa)
{

	umtx_key_release(&fa->fa_key);
}