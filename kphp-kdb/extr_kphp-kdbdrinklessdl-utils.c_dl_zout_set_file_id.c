#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int id; scalar_t__ written; } ;
typedef  TYPE_1__ dl_zout ;

/* Variables and functions */

void dl_zout_set_file_id (dl_zout *f, int fid) {
  f->id = fid;
  f->written = 0;
}