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
 int umtx_key_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
futex_address_match(const struct futex_address *fa1,
    const struct futex_address *fa2)
{

	return (umtx_key_match(&fa1->fa_key, &fa2->fa_key));
}