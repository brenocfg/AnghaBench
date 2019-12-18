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
struct feed_eq_info {int /*<<< orphan*/ * coeff; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * feed_eq_coeff_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feed_eq_reset (struct feed_eq_info*) ; 

__attribute__((used)) static int
feed_eq_setup(struct feed_eq_info *info)
{

	info->coeff = feed_eq_coeff_rate(info->rate);
	if (info->coeff == NULL)
		return (EINVAL);

	feed_eq_reset(info);

	return (0);
}