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
struct hts_data {int /*<<< orphan*/ * extra; } ;
struct connection {int dummy; } ;
typedef  int /*<<< orphan*/  php_worker ;

/* Variables and functions */
 struct hts_data* HTS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int php_worker_main (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_worker_terminate (int /*<<< orphan*/ *,int,char*) ; 

int hts_func_close (struct connection *c, int who) {
  struct hts_data *D = HTS_DATA(c);

  php_worker *worker = D->extra;
  if (worker != NULL) {
    php_worker_terminate (worker, 1, "http connection close");
    int res = php_worker_main (worker);
    D->extra = NULL;
    assert ("worker is unfinished after closing connection" && res == 1);
  }
  return 0;
}