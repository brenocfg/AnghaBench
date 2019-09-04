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
struct file_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIF_ERROR ; 
 scalar_t__ read_file_header (struct file_info*) ; 

__attribute__((used)) static int read_file_headers (struct file_info *files, int fnum) {
  int res = 0, i;
  for (i = 0; i < fnum; i++) {
    if (read_file_header (files + i) >= 0) {
      res++;
    } else {
      files[i].flags |= FIF_ERROR;
    }
  }
  return res;
}