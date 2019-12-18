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
struct hwrng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct hwrng* current_rng ; 
 int /*<<< orphan*/  drop_current_rng () ; 
 int hwrng_init (struct hwrng*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rng_mutex ; 

__attribute__((used)) static int set_current_rng(struct hwrng *rng)
{
	int err;

	BUG_ON(!mutex_is_locked(&rng_mutex));

	err = hwrng_init(rng);
	if (err)
		return err;

	drop_current_rng();
	current_rng = rng;

	return 0;
}