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
typedef  int /*<<< orphan*/  iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  int /*<<< orphan*/  iwdp_idl_t ;

/* Variables and functions */
 int /*<<< orphan*/  IWDP_SUCCESS ; 

iwdp_status iwdp_idl_close(iwdp_t self, iwdp_idl_t idl) {
  // TODO rm_fd all device_id_to_iport s_fds?!
  return IWDP_SUCCESS;
}