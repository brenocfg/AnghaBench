#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int weight; scalar_t__ p; } ;
struct TYPE_5__ {int p; int weight; } ;
struct TYPE_4__ {int p; int weight; int /*<<< orphan*/ * f; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ENTRY_SORT_SEARCH ; 
 int FLAG_REVERSE_SEARCH ; 
 size_t MAX_RATE_WEIGHTS ; 
 int M_LN2 ; 
 TYPE_3__ QRP ; 
 TYPE_2__ QRT ; 
 scalar_t__ QRT_min_creation_time ; 
 TYPE_1__* QRW ; 
 int /*<<< orphan*/  Q_order ; 
 int get_sorting_mode (int) ; 
 scalar_t__ now ; 
 size_t query_rate_weights ; 
 int /*<<< orphan*/ * rw_func_linear ; 
 int /*<<< orphan*/ * rw_func_linear_reverse ; 
 int /*<<< orphan*/ * rw_func_log ; 
 int /*<<< orphan*/ * rw_func_log_reverse ; 

__attribute__((used)) static int rate_weight_add (int func_tp, int tp, int weight) {
  if (weight <= 0) {
    return 0;
  }
  if (query_rate_weights >= MAX_RATE_WEIGHTS) { return -3; }

  if (tp == 'P') {
    if (func_tp == 'l') {
      QRP.p = 0;
      QRP.weight = weight;
      QRW[query_rate_weights].f = NULL;
      Q_order |= FLAG_ENTRY_SORT_SEARCH;
      return 0;
    }
    return -4;
  }

  int p = get_sorting_mode (tp);
  if (p < 0) { return -1; }
  int reverse_search = p & FLAG_REVERSE_SEARCH;
  QRW[query_rate_weights].p = p & 15;
  QRW[query_rate_weights].weight = weight;
  if (func_tp == 'L') {
    QRW[query_rate_weights].f = reverse_search ? rw_func_log_reverse : rw_func_log;
  } else if (func_tp == 'l') {
    QRW[query_rate_weights].f = reverse_search ? rw_func_linear_reverse : rw_func_linear;
  } else if (func_tp == 'T') {
    QRT.p = QRW[query_rate_weights].p;
    QRT.weight = -(M_LN2 / weight);
    QRT_min_creation_time = now - weight * 40;
    return 0;
  } else {
    return -2;
  }
  query_rate_weights++;
  return 0;
}