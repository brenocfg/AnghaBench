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
struct TYPE_4__ {unsigned int sec; int /*<<< orphan*/  nsec; } ;
struct TYPE_3__ {unsigned int sec; int /*<<< orphan*/  nsec; } ;
struct stat_data {int /*<<< orphan*/  sd_size; int /*<<< orphan*/  sd_gid; int /*<<< orphan*/  sd_uid; int /*<<< orphan*/  sd_ino; int /*<<< orphan*/  sd_dev; TYPE_2__ sd_mtime; TYPE_1__ sd_ctime; } ;
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; scalar_t__ st_mtime; scalar_t__ st_ctime; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_CTIME_NSEC (struct stat) ; 
 int /*<<< orphan*/  ST_MTIME_NSEC (struct stat) ; 

void fill_stat_data(struct stat_data *sd, struct stat *st)
{
	sd->sd_ctime.sec = (unsigned int)st->st_ctime;
	sd->sd_mtime.sec = (unsigned int)st->st_mtime;
	sd->sd_ctime.nsec = ST_CTIME_NSEC(*st);
	sd->sd_mtime.nsec = ST_MTIME_NSEC(*st);
	sd->sd_dev = st->st_dev;
	sd->sd_ino = st->st_ino;
	sd->sd_uid = st->st_uid;
	sd->sd_gid = st->st_gid;
	sd->sd_size = st->st_size;
}