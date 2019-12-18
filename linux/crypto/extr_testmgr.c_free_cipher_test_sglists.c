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
struct cipher_test_sglists {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_test_sglist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cipher_test_sglists*) ; 

__attribute__((used)) static void free_cipher_test_sglists(struct cipher_test_sglists *tsgls)
{
	if (tsgls) {
		destroy_test_sglist(&tsgls->src);
		destroy_test_sglist(&tsgls->dst);
		kfree(tsgls);
	}
}