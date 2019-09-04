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
struct TYPE_3__ {int n; scalar_t__* r; int /*<<< orphan*/ ** k; } ;
typedef  TYPE_1__ qkey_group ;

/* Variables and functions */
 int __may_wait ; 
 int /*<<< orphan*/  buff_overflow_cnt ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 char* debug_buff ; 
 scalar_t__ debug_error ; 
 char* ds ; 
 int /*<<< orphan*/  get_events_http (int /*<<< orphan*/ *) ; 
 scalar_t__* http_failed ; 
 int quick_fix ; 

char *get_events_http_group (qkey_group *k) {
  ds = debug_buff;
  __may_wait = 1;

  quick_fix = 1;
  if (k->n > 1) {
    debug ("[");
  }
  int i, http_ok = 0;
  for (i = 0; i < k->n; i++) {
    if (k->k[i] != NULL) {
      get_events_http (k->k[i]);
      http_ok++;
    } else {
      int err = (int)k->r[i];
      debug ("{\"failed\":2,\"err\":%d}", err);
      __may_wait = 0;
      http_failed[2 + err / 4]++;
    }
    if (debug_error) {
      quick_fix = 0;

      http_failed[3]++;
      buff_overflow_cnt++;

      debug_error = 0;
      ds = debug_buff;
      debug ("{\"failed\":3}");

      return debug_buff;
    }
    if (i + 1 != k->n) {
      debug (",");
    }
  }
  if (k->n > 1) {
    debug ("]");
  }
  if (!__may_wait) {
    http_failed[0] += http_ok;
  }

  quick_fix = 0;
  return debug_buff;
}