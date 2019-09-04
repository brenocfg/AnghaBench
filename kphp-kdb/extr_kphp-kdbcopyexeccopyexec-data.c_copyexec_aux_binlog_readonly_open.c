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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  fd_aux_binlog ; 
 int /*<<< orphan*/  kprintf (char*,char const* const) ; 
 int /*<<< orphan*/  open (char const* const,int /*<<< orphan*/ ) ; 

int copyexec_aux_binlog_readonly_open (const char *const aux_binlog_name) {
  if (aux_binlog_name == NULL || (fd_aux_binlog = open (aux_binlog_name, O_RDONLY)) < 0) {
    kprintf ("Couldn't open aux binlog \"%s\" in read only mode. %m\n", aux_binlog_name);
    return -1;
  }

  return 0;
}