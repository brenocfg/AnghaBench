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
struct qlnxr_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qlnxr_add_default_sgid (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  qlnxr_add_sgids (struct qlnxr_dev*) ; 

__attribute__((used)) static int
qlnxr_build_sgid_tbl(struct qlnxr_dev *dev)
{
	qlnxr_add_default_sgid(dev);
	qlnxr_add_sgids(dev);
	return 0;
}