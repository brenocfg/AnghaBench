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
struct TYPE_3__ {scalar_t__ drive_old_mx; scalar_t__ drive_mx; scalar_t__ drive_r; scalar_t__ drive_l; } ;
typedef  TYPE_1__ one_header ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void upd_mx (one_header *data) {
  if (data->drive_old_mx < data->drive_mx) {
    assert (data->drive_r < data->drive_old_mx && data->drive_l <= data->drive_r);
  }
  data->drive_old_mx = data->drive_mx;
}