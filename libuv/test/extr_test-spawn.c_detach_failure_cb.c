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
typedef  int /*<<< orphan*/  uv_process_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit_cb_called ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void detach_failure_cb(uv_process_t* process,
                              int64_t exit_status,
                              int term_signal) {
  printf("detach_cb\n");
  exit_cb_called++;
}