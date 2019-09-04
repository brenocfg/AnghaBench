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

/* Variables and functions */
 int MAX_ACCOUNT_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 int sprintf (char*,char*,long long) ; 

char *store_acc_id (char *to, int acc_type_id, long long acc_id) {
  int x;
  assert (acc_type_id >= 0 && acc_type_id <= MAX_ACCOUNT_TYPE);
  if (acc_type_id >= 27 * 27) {
    *to++ = 64 + (acc_type_id / (27 * 27));
  }
  if (acc_type_id >= 27) {
    x = acc_type_id / 27 % 27;
    *to++ = (x > 0 ? 64 + x : '_');
  }
  if (acc_type_id) {
    x = acc_type_id % 27;
    *to++ = (x > 0 ? 64 + x : '_');
  }
  return to + sprintf (to, "%lld", acc_id);
}