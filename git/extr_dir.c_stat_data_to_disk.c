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
struct TYPE_4__ {void* nsec; void* sec; } ;
struct TYPE_3__ {void* nsec; void* sec; } ;
struct stat_data {void* sd_size; void* sd_gid; void* sd_uid; void* sd_ino; void* sd_dev; TYPE_2__ sd_mtime; TYPE_1__ sd_ctime; } ;

/* Variables and functions */
 void* htonl (void*) ; 

__attribute__((used)) static void stat_data_to_disk(struct stat_data *to, const struct stat_data *from)
{
	to->sd_ctime.sec  = htonl(from->sd_ctime.sec);
	to->sd_ctime.nsec = htonl(from->sd_ctime.nsec);
	to->sd_mtime.sec  = htonl(from->sd_mtime.sec);
	to->sd_mtime.nsec = htonl(from->sd_mtime.nsec);
	to->sd_dev	  = htonl(from->sd_dev);
	to->sd_ino	  = htonl(from->sd_ino);
	to->sd_uid	  = htonl(from->sd_uid);
	to->sd_gid	  = htonl(from->sd_gid);
	to->sd_size	  = htonl(from->sd_size);
}