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
typedef  int /*<<< orphan*/  transaction_t ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_transaction_dir (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_transaction_hash (int /*<<< orphan*/ *,char*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static void get_transaction_binlog_name (transaction_t *T, char binlog_name[PATH_MAX]) {
  char dir[PATH_MAX], b[28];
  get_transaction_dir (T, dir);
  get_transaction_hash (T, b);
  assert (snprintf (binlog_name, PATH_MAX, "%s/.binlog.%s", dir, b) < PATH_MAX);
}