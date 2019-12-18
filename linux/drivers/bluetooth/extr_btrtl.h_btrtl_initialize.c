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
struct hci_dev {int dummy; } ;
struct btrtl_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct btrtl_device_info* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct btrtl_device_info *btrtl_initialize(struct hci_dev *hdev,
							 const char *postfix)
{
	return ERR_PTR(-EOPNOTSUPP);
}