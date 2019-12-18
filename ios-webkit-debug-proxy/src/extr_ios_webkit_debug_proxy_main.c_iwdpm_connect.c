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

/* Variables and functions */
 int sm_connect (char const*) ; 

int iwdpm_connect(iwdp_t iwdp, const char *socket_addr) {
  return sm_connect(socket_addr);
}