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
typedef  int /*<<< orphan*/  olist_t ;

/* Variables and functions */
 int /*<<< orphan*/ * OHead ; 
 int OLIST_COUNT ; 
 int ocur_now ; 
 int online_convert_time (int) ; 
 int /*<<< orphan*/  online_list_unpack (int*,int /*<<< orphan*/ *) ; 

int online_interval_unpack (int *A, int bt, int et) {
  if (bt > et || bt > ocur_now) {
    return 0;
  }
  int i;
  int *PA = A;
  int bp = online_convert_time (bt);
  int ep = online_convert_time (et);
  if (bp <= ep) {
    for (i = bp; i <= ep; i++) {
      A += online_list_unpack (A, (olist_t *)&OHead[i]);
    }
  } else {
    for (i = bp; i < OLIST_COUNT; i++) {
      A += online_list_unpack (A, (olist_t *)&OHead[i]);
    }
    for (i = 0; i <= ep; i++) {
      A += online_list_unpack (A, (olist_t *)&OHead[i]);
    }
  }
  return A - PA;
}