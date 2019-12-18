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
struct fw_device {int /*<<< orphan*/ * config_rom; } ;
struct fw_csr_iterator {scalar_t__ p; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int CSR_DIRECTORY ; 
 int CSR_UNIT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int /*<<< orphan*/ *) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 
 struct fw_device* fw_device (struct device*) ; 
 int /*<<< orphan*/  fw_device_rwsem ; 
 scalar_t__ units_sprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t units_show(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct fw_device *device = fw_device(dev);
	struct fw_csr_iterator ci;
	int key, value, i = 0;

	down_read(&fw_device_rwsem);
	fw_csr_iterator_init(&ci, &device->config_rom[5]);
	while (fw_csr_iterator_next(&ci, &key, &value)) {
		if (key != (CSR_UNIT | CSR_DIRECTORY))
			continue;
		i += units_sprintf(&buf[i], ci.p + value - 1);
		if (i >= PAGE_SIZE - (8 + 1 + 8 + 1))
			break;
	}
	up_read(&fw_device_rwsem);

	if (i)
		buf[i - 1] = '\n';

	return i;
}