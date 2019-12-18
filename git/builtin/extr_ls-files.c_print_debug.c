#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sec; int nsec; } ;
struct TYPE_3__ {int sec; int nsec; } ;
struct stat_data {int sd_dev; int sd_ino; int sd_uid; int sd_gid; int sd_size; TYPE_2__ sd_mtime; TYPE_1__ sd_ctime; } ;
struct cache_entry {int ce_flags; struct stat_data ce_stat_data; } ;

/* Variables and functions */
 scalar_t__ debug_mode ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void print_debug(const struct cache_entry *ce)
{
	if (debug_mode) {
		const struct stat_data *sd = &ce->ce_stat_data;

		printf("  ctime: %u:%u\n", sd->sd_ctime.sec, sd->sd_ctime.nsec);
		printf("  mtime: %u:%u\n", sd->sd_mtime.sec, sd->sd_mtime.nsec);
		printf("  dev: %u\tino: %u\n", sd->sd_dev, sd->sd_ino);
		printf("  uid: %u\tgid: %u\n", sd->sd_uid, sd->sd_gid);
		printf("  size: %u\tflags: %x\n", sd->sd_size, ce->ce_flags);
	}
}