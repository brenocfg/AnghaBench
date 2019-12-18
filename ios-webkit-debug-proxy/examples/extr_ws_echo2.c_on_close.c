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
typedef  int /*<<< orphan*/  sm_t ;
typedef  int /*<<< orphan*/  sm_status ;
typedef  int /*<<< orphan*/  my_t ;

/* Variables and functions */
 int /*<<< orphan*/  SM_SUCCESS ; 
 int /*<<< orphan*/  my_free (int /*<<< orphan*/ ) ; 

sm_status on_close(sm_t sm, int fd, void *value, bool is_server) {
  if (!is_server) {
    my_free((my_t)value);
  }
  return SM_SUCCESS;
}