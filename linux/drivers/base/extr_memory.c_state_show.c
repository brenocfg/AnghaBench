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
struct memory_block {int state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  MEM_GOING_OFFLINE 130 
#define  MEM_OFFLINE 129 
#define  MEM_ONLINE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct memory_block* to_memory_block (struct device*) ; 

__attribute__((used)) static ssize_t state_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct memory_block *mem = to_memory_block(dev);
	ssize_t len = 0;

	/*
	 * We can probably put these states in a nice little array
	 * so that they're not open-coded
	 */
	switch (mem->state) {
	case MEM_ONLINE:
		len = sprintf(buf, "online\n");
		break;
	case MEM_OFFLINE:
		len = sprintf(buf, "offline\n");
		break;
	case MEM_GOING_OFFLINE:
		len = sprintf(buf, "going-offline\n");
		break;
	default:
		len = sprintf(buf, "ERROR-UNKNOWN-%ld\n",
				mem->state);
		WARN_ON(1);
		break;
	}

	return len;
}