#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double weight; scalar_t__ p; } ;
struct TYPE_3__ {int p; double weight; scalar_t__ f; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ENTRY_SORT_SEARCH ; 
 size_t MAX_RATE_WEIGHTS ; 
 TYPE_2__ QRP ; 
 TYPE_1__* QRW ; 
 int /*<<< orphan*/  Q_order ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t query_rate_weights ; 
 scalar_t__ rw_func_linear ; 
 scalar_t__ rw_func_linear_reverse ; 
 scalar_t__ rw_func_log ; 
 scalar_t__ rw_func_log_reverse ; 

void add_rate_weight (int rate_type, double weight, int flags) {
  if (weight <= 0) {
    return;
  }
  assert (query_rate_weights < MAX_RATE_WEIGHTS);
  if (rate_type == -1) {
    QRP.p = 0;
    QRP.weight = weight;
    QRW[query_rate_weights].f = 0;
    Q_order |= FLAG_ENTRY_SORT_SEARCH;
    return;
  }
  int reverse_search = flags & 1;
  QRW[query_rate_weights].p = rate_type;
  QRW[query_rate_weights].weight = weight;
  if (flags & 2) {
    QRW[query_rate_weights].f = reverse_search ? rw_func_log_reverse : rw_func_log;
  } else {
    QRW[query_rate_weights].f = reverse_search ? rw_func_linear_reverse : rw_func_linear;
  }
  query_rate_weights++;
}