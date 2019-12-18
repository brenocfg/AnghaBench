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
 int /*<<< orphan*/  Entry ; 
 int /*<<< orphan*/  ans ; 
 scalar_t__ ans_n ; 
 int /*<<< orphan*/  dl_qsort_addr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  process_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  watchcat_prepare_entry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

char *gen_addrs (char *s) {
  // s == text 0x1 info
  char *t = s;
  int f = 0;
  while (*t) {
    if (*t++ == 1) {
      f = 1;
      t[-1] = 0;
      break;
    }
  }

  watchcat_prepare_entry (&Entry, s, strlen (s));

  if (f) {
    t[-1] = 1;
  } else {
    t = s;
  }

  ans_n = 0;
  process_entry(&Entry);
  dl_qsort_addr (ans, ans_n);
  return t;
}