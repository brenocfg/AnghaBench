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
struct TYPE_3__ {scalar_t__ size; } ;
typedef  TYPE_1__ metafile_t ;

/* Variables and functions */
 scalar_t__ meta_header_size ; 

__attribute__((used)) static int get_meta_bucket (metafile_t *meta) {
  int r = 0;
  if (meta->size > 65536 + meta_header_size) {
    r++;
  }
  return r;
}