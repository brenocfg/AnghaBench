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
typedef  int /*<<< orphan*/  dl_zout ;

/* Variables and functions */
 int /*<<< orphan*/  dl_zout_raw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_zout_set_buffer_len (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dl_zout_set_crc32_flag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dl_zout_set_file_id (int /*<<< orphan*/ *,int) ; 

void dl_zout_init (dl_zout *f, int id, int len) {
  dl_zout_raw_init (f);

  dl_zout_set_file_id (f, id);
  dl_zout_set_buffer_len (f, len);
  dl_zout_set_crc32_flag (f, 1);
}