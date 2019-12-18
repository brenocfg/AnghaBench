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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  sm_t ;
typedef  int /*<<< orphan*/  sm_status ;

/* Variables and functions */
 int /*<<< orphan*/  SM_SUCCESS ; 

sm_status iwdpm_on_sent(sm_t sm, int fd, void *value,
    const char *buf, ssize_t length) {
  return SM_SUCCESS;
}