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
struct sscfu {int /*<<< orphan*/  sigs; scalar_t__ inhand; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGQ_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSCFU_RELEASED ; 

void
sscfu_reset(struct sscfu *sscf)
{
	sscf->state = SSCFU_RELEASED;
	sscf->inhand = 0;
	SIGQ_CLEAR(&sscf->sigs);
}