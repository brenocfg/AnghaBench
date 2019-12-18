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
struct opal_dev {int /*<<< orphan*/ * prev_data; scalar_t__ hsn; scalar_t__ tsn; } ;

/* Variables and functions */

__attribute__((used)) static inline void setup_opal_dev(struct opal_dev *dev)
{
	dev->tsn = 0;
	dev->hsn = 0;
	dev->prev_data = NULL;
}