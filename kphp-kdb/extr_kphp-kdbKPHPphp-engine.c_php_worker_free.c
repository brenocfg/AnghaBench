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
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ php_worker ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  php_query_data_free (int /*<<< orphan*/ *) ; 

void php_worker_free (php_worker *worker) {
  if (worker == NULL) {
    return;
  }

  php_query_data_free (worker->data);
  worker->data = NULL;

  dl_free (worker, sizeof (php_worker));
}