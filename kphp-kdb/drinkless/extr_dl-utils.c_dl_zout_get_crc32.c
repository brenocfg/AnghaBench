#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int crc32_complement; } ;
typedef  TYPE_1__ dl_zout ;

/* Variables and functions */
 int /*<<< orphan*/  dl_zout_flush (TYPE_1__*) ; 

unsigned int dl_zout_get_crc32 (dl_zout *f) {
  //TODO: make it with f->crc32_ptr
  dl_zout_flush (f);
  return ~f->crc32_complement;
}