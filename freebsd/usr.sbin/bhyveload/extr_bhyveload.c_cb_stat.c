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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int st_mode; int st_uid; int st_gid; int /*<<< orphan*/  st_size; } ;
struct cb_file {TYPE_1__ cf_stat; } ;

/* Variables and functions */

__attribute__((used)) static int
cb_stat(void *arg, void *h, int *mode, int *uid, int *gid, uint64_t *size)
{
	struct cb_file *cf = h;

	*mode = cf->cf_stat.st_mode;
	*uid = cf->cf_stat.st_uid;
	*gid = cf->cf_stat.st_gid;
	*size = cf->cf_stat.st_size;
	return (0);
}