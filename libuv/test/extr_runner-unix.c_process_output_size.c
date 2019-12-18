#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  stdout_file; } ;
typedef  TYPE_1__ process_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 

long int process_output_size(process_info_t *p) {
  /* Size of the p->stdout_file */
  struct stat buf;

  int r = fstat(fileno(p->stdout_file), &buf);
  if (r < 0) {
    return -1;
  }

  return (long)buf.st_size;
}