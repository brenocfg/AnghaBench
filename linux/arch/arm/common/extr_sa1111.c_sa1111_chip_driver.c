#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct sa1111_dev {TYPE_1__ dev; } ;
struct sa1111 {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sa1111 *sa1111_chip_driver(struct sa1111_dev *sadev)
{
	return (struct sa1111 *)dev_get_drvdata(sadev->dev.parent);
}