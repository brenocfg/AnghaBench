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
typedef  int /*<<< orphan*/  u32 ;
struct mthca_eq {int dummy; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arbel_set_eq_ci (struct mthca_dev*,struct mthca_eq*,int /*<<< orphan*/ ) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  tavor_set_eq_ci (struct mthca_dev*,struct mthca_eq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_eq_ci(struct mthca_dev *dev, struct mthca_eq *eq, u32 ci)
{
	if (mthca_is_memfree(dev))
		arbel_set_eq_ci(dev, eq, ci);
	else
		tavor_set_eq_ci(dev, eq, ci);
}