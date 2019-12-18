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
struct cipher_test_sglists {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  destroy_test_sglist (int /*<<< orphan*/ *) ; 
 scalar_t__ init_test_sglist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cipher_test_sglists*) ; 
 struct cipher_test_sglists* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cipher_test_sglists *alloc_cipher_test_sglists(void)
{
	struct cipher_test_sglists *tsgls;

	tsgls = kmalloc(sizeof(*tsgls), GFP_KERNEL);
	if (!tsgls)
		return NULL;

	if (init_test_sglist(&tsgls->src) != 0)
		goto fail_kfree;
	if (init_test_sglist(&tsgls->dst) != 0)
		goto fail_destroy_src;

	return tsgls;

fail_destroy_src:
	destroy_test_sglist(&tsgls->src);
fail_kfree:
	kfree(tsgls);
	return NULL;
}