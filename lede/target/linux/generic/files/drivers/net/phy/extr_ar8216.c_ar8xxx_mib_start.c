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
struct ar8xxx_priv {int /*<<< orphan*/  mib_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8XXX_MIB_WORK_DELAY ; 
 int /*<<< orphan*/  ar8xxx_has_mib_counters (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar8xxx_mib_start(struct ar8xxx_priv *priv)
{
	if (!ar8xxx_has_mib_counters(priv))
		return;

	schedule_delayed_work(&priv->mib_work,
			      msecs_to_jiffies(AR8XXX_MIB_WORK_DELAY));
}