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
struct gather_entry {int res_read; int* data; } ;

/* Variables and functions */
 int PHP_MAX_RES ; 
 int /*<<< orphan*/ * Q ; 
 int Q_limit ; 

__attribute__((used)) static void gather_sum_res (struct gather_entry *GE) {
  int cnt = (GE->res_read >> 2) - 1;
  int *ptr = GE->data;
  int i;

  if (cnt > PHP_MAX_RES) { cnt = PHP_MAX_RES; }
  if (cnt > Q_limit) { Q_limit = cnt; }
  for (i = 0; i < cnt; i++) {
    Q[i] += *ptr++;
  }
}