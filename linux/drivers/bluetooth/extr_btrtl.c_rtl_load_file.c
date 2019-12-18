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
typedef  int /*<<< orphan*/  u8 ;
struct hci_dev {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_dev_info (struct hci_dev*,char*,char const*) ; 

__attribute__((used)) static int rtl_load_file(struct hci_dev *hdev, const char *name, u8 **buff)
{
	const struct firmware *fw;
	int ret;

	rtl_dev_info(hdev, "loading %s", name);
	ret = request_firmware(&fw, name, &hdev->dev);
	if (ret < 0)
		return ret;
	ret = fw->size;
	*buff = kmemdup(fw->data, ret, GFP_KERNEL);
	if (!*buff)
		ret = -ENOMEM;

	release_firmware(fw);

	return ret;
}