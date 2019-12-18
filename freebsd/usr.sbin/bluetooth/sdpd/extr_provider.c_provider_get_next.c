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
typedef  int /*<<< orphan*/  provider_p ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  provider_next ; 

provider_p
provider_get_next(provider_p provider)
{
	return (TAILQ_NEXT(provider, provider_next));
}