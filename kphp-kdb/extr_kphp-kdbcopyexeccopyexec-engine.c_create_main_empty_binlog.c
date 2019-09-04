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
struct lev_copyexec_main_transaction_skip {int first_transaction_id; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  E ;

/* Variables and functions */
 int /*<<< orphan*/  COPYEXEC_MAIN_SCHEMA_V1 ; 
 int /*<<< orphan*/  LEV_COPYEXEC_MAIN_TRANSACTION_SKIP ; 
 int /*<<< orphan*/  empty_binlog_volume_name ; 
 int /*<<< orphan*/  exit (int) ; 
 int find_last_synchronization_point () ; 
 int get_random_bytes (int*,int) ; 
 int instance_mask ; 
 int /*<<< orphan*/  kprintf (char*,int const) ; 
 int /*<<< orphan*/  make_empty_binlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,void*,int) ; 

__attribute__((used)) static void create_main_empty_binlog (char *binlog_name) {
  void *extra = NULL;
  int extra_len = 0;
  struct lev_copyexec_main_transaction_skip E;

  int lev_start_extra[3];
  lev_start_extra[2] = instance_mask;

  int r = get_random_bytes (lev_start_extra, 8);
  if (r != 8) {
    kprintf ("random_tag creation failed, get_random_bytes returns %d instead of 8.\n", r);
    exit (1);
  }

  const int sp = find_last_synchronization_point ();
  if (sp) {
    kprintf ("Last synchronization point transaction id is %d.\n", sp);
    E.type = LEV_COPYEXEC_MAIN_TRANSACTION_SKIP;
    E.first_transaction_id = sp + 1;
    extra = &E;
    extra_len = sizeof (E);
  }

  make_empty_binlog (binlog_name, empty_binlog_volume_name, COPYEXEC_MAIN_SCHEMA_V1, lev_start_extra, 12, extra, extra_len);

}