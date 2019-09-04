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
 int COMMIT_LOG_BUFF_SIZE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 char* binlog_name ; 
 int /*<<< orphan*/  close (int) ; 
 int committed_transaction_size ; 
 int open (char*,int,int) ; 
 int snprintf (char*,int,char*,...) ; 
 char* transaction_dirname ; 
 int transactions ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void write_commit_log (void) {
  char a[PATH_MAX], b[COMMIT_LOG_BUFF_SIZE];
  assert (snprintf (a, PATH_MAX, "%s/.commit.log", transaction_dirname) < PATH_MAX);
  int fd = open (a, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0640);
  int n = snprintf (b, COMMIT_LOG_BUFF_SIZE,
    "transaction_id\t%d\n"
    "committed_transaction_size\t%u\n"
    "aux_binlog_path\t%s\n",
    transactions,
    committed_transaction_size,
    binlog_name);
  if (n > COMMIT_LOG_BUFF_SIZE - 1) {
    n = COMMIT_LOG_BUFF_SIZE - 1;
  }
  write (fd, b, n);
  close (fd);
}