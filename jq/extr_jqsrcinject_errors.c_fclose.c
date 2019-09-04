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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  GET_REAL (int (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/ * fail ; 
 int /*<<< orphan*/ * fail_close ; 
 int /*<<< orphan*/ * fail_read ; 
 int /*<<< orphan*/ * fail_write ; 
 int real_fclose (int /*<<< orphan*/ *) ; 

int fclose(FILE *f) {
  GET_REAL(fclose);
  int res = real_fclose(f);
  if (fail_close == f) {
    fail = fail_read = fail_write = fail_close = 0;
    return EOF;
  }
  return res;
}