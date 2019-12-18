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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ata_device {scalar_t__ class; int* id; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ATA_DEV_PMP ; 
 int ATA_ID_WORDS ; 
 scalar_t__ snprintf (char*,int,char*,int,char) ; 
 struct ata_device* transport_class_to_dev (struct device*) ; 

__attribute__((used)) static ssize_t
show_ata_dev_id(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct ata_device *ata_dev = transport_class_to_dev(dev);
	int written = 0, i = 0;

	if (ata_dev->class == ATA_DEV_PMP)
		return 0;
	for(i=0;i<ATA_ID_WORDS;i++)  {
		written += snprintf(buf+written, 20, "%04x%c",
				    ata_dev->id[i],
				    ((i+1) & 7) ? ' ' : '\n');
	}
	return written;
}