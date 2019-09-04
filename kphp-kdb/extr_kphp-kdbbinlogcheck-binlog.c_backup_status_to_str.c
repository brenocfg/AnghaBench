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
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int bs_differ ; 
 int bs_io_error ; 
 int bs_larger ; 
 int bs_same_inode ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

char *backup_status_to_str (int status) {
  static char out[64];
  char *p = out;
  p[0] = p[1] = 0;
  if (status & bs_differ) {
    p += sprintf (p, "|differ");
  }
  if (status & bs_io_error) {
    p += sprintf (p, "|io_error");
  }
  if (status & bs_larger) {
    p += sprintf (p, "|larger");
  }
  if (status & bs_same_inode) {
    p += sprintf (p, "|same_inode");
  }
  assert (p < out + sizeof (out));
  return out+1;
}