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
typedef  int /*<<< orphan*/  qkey ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  keys_cnt ; 
 int /*<<< orphan*/  keys_memory ; 

void qkey_free (qkey *q) {
  keys_cnt--;

  keys_memory -= dl_get_memory_used();
  dl_free (q, sizeof (qkey));
  keys_memory += dl_get_memory_used();
  /*
  q->name = (char *)qks;
  qks = q;
  */
}