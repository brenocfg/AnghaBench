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
struct TYPE_3__ {int terminate_flag; char const* error_message; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ php_worker ;

/* Variables and functions */
 int /*<<< orphan*/  vkprintf (int /*<<< orphan*/ ,char*) ; 

void php_worker_terminate (php_worker *worker, int flag, const char *error_message) {
  worker->terminate_flag = 1;
  worker->error_message = error_message;
  if (flag) {
    vkprintf (0, "php_worker_terminate\n");
    worker->conn = NULL;
  }
}