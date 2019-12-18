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
struct mfp_pin {int /*<<< orphan*/  mfpr_run; int /*<<< orphan*/  mfpr_off; } ;

/* Variables and functions */
 scalar_t__ mfp_configured (struct mfp_pin*) ; 
 int /*<<< orphan*/  mfpr_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __mfp_config_run(struct mfp_pin *p)
{
	if (mfp_configured(p))
		mfpr_writel(p->mfpr_off, p->mfpr_run);
}