#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct tegra_ivc_header {TYPE_2__ rx; TYPE_1__ tx; } ;
struct tegra_ivc {int dummy; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 tegra_ivc_available(struct tegra_ivc *ivc,
				      struct tegra_ivc_header *header)
{
	u32 tx = READ_ONCE(header->tx.count);
	u32 rx = READ_ONCE(header->rx.count);

	/*
	 * This function isn't expected to be used in scenarios where an
	 * over-full situation can lead to denial of service attacks. See the
	 * comment in tegra_ivc_empty() for an explanation about special
	 * over-full considerations.
	 */
	return tx - rx;
}