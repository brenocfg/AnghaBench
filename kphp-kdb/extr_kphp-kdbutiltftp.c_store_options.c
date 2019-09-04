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
 scalar_t__ sprintf (char*,char*,long long) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *store_options (char *wptr, int block_size, int timeout, long long tsize) {
  if (block_size > 0) {
    strcpy (wptr, "blksize");
    wptr += 8;
    wptr += sprintf (wptr, "%d", block_size) + 1;
  }
  if (timeout > 0) {
    strcpy (wptr, "timeout");
    wptr += 8;
    wptr += sprintf (wptr, "%d", timeout) + 1;
  }
  if (tsize >= 0) {
    strcpy (wptr, "tsize");
    wptr += 6;
    wptr += sprintf (wptr, "%lld", tsize) + 1;
  }
  return wptr;
}