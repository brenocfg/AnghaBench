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
struct request_queue {int dummy; } ;
struct hd_struct {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 size_t STAT_DISCARD ; 
 size_t STAT_READ ; 
 size_t STAT_WRITE ; 
 struct hd_struct* dev_to_part (struct device*) ; 
 int /*<<< orphan*/  io_ticks ; 
 int /*<<< orphan*/ * ios ; 
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 int /*<<< orphan*/ * merges ; 
 unsigned int part_in_flight (struct request_queue*,struct hd_struct*) ; 
 int part_stat_read (struct hd_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ part_stat_read_msecs (struct hd_struct*,size_t) ; 
 TYPE_1__* part_to_disk (struct hd_struct*) ; 
 int /*<<< orphan*/ * sectors ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,unsigned long long,unsigned int,int,int,unsigned long long,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned long long,unsigned int) ; 
 int /*<<< orphan*/  time_in_queue ; 

ssize_t part_stat_show(struct device *dev,
		       struct device_attribute *attr, char *buf)
{
	struct hd_struct *p = dev_to_part(dev);
	struct request_queue *q = part_to_disk(p)->queue;
	unsigned int inflight;

	inflight = part_in_flight(q, p);
	return sprintf(buf,
		"%8lu %8lu %8llu %8u "
		"%8lu %8lu %8llu %8u "
		"%8u %8u %8u "
		"%8lu %8lu %8llu %8u"
		"\n",
		part_stat_read(p, ios[STAT_READ]),
		part_stat_read(p, merges[STAT_READ]),
		(unsigned long long)part_stat_read(p, sectors[STAT_READ]),
		(unsigned int)part_stat_read_msecs(p, STAT_READ),
		part_stat_read(p, ios[STAT_WRITE]),
		part_stat_read(p, merges[STAT_WRITE]),
		(unsigned long long)part_stat_read(p, sectors[STAT_WRITE]),
		(unsigned int)part_stat_read_msecs(p, STAT_WRITE),
		inflight,
		jiffies_to_msecs(part_stat_read(p, io_ticks)),
		jiffies_to_msecs(part_stat_read(p, time_in_queue)),
		part_stat_read(p, ios[STAT_DISCARD]),
		part_stat_read(p, merges[STAT_DISCARD]),
		(unsigned long long)part_stat_read(p, sectors[STAT_DISCARD]),
		(unsigned int)part_stat_read_msecs(p, STAT_DISCARD));
}