#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ fd; } ;

/* Variables and functions */
 char* BINLOG_NAME ; 
 TYPE_1__* CC ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ open (char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

void open_binlog_file (void) {
  CC->fd = open (BINLOG_NAME, O_RDWR | O_CREAT, 0600);
  if (CC->fd < 0) {
    fprintf (stderr, "can not open file for replication (error %m)\n");
    fprintf (stderr, "file %s\n", BINLOG_NAME);
    exit (1);
  }
}