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

/* Variables and functions */
 int /*<<< orphan*/  BIOSET_NEED_BVECS ; 
 int /*<<< orphan*/  BIO_POOL_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int bioset_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bioset_integrity_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bounce_bio_set ; 
 int /*<<< orphan*/  bounce_bio_split ; 

__attribute__((used)) static void init_bounce_bioset(void)
{
	static bool bounce_bs_setup;
	int ret;

	if (bounce_bs_setup)
		return;

	ret = bioset_init(&bounce_bio_set, BIO_POOL_SIZE, 0, BIOSET_NEED_BVECS);
	BUG_ON(ret);
	if (bioset_integrity_create(&bounce_bio_set, BIO_POOL_SIZE))
		BUG_ON(1);

	ret = bioset_init(&bounce_bio_split, BIO_POOL_SIZE, 0, 0);
	BUG_ON(ret);
	bounce_bs_setup = true;
}