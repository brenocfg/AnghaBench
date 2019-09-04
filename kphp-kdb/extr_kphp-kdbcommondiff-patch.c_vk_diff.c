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
typedef  int /*<<< orphan*/  dyn_mark_t ;

/* Variables and functions */
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int find_diff (unsigned char*,int,unsigned char*,int,unsigned char*,int,int,double) ; 

int vk_diff (unsigned char *old_buff, int old_buff_size, unsigned char *new_buff, int new_buff_size, unsigned char *patch_buff, int patch_buff_size, int compress_level, double timeout) {
  dyn_mark_t mrk;
  dyn_mark (mrk);
  int r = find_diff (old_buff, old_buff_size, new_buff, new_buff_size, patch_buff, patch_buff_size, compress_level, timeout);
  dyn_release (mrk);
  return r;
}