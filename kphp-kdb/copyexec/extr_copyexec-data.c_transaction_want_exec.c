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
struct TYPE_3__ {scalar_t__ status; int mask; int result; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 int MASK_RERUN_TRANSACTION ; 
 scalar_t__ SIGINT ; 
 scalar_t__ SIGTERM ; 
 scalar_t__ ts_cancelled ; 
 scalar_t__ ts_decryption_failed ; 
 scalar_t__ ts_interrupted ; 
 scalar_t__ ts_running ; 

__attribute__((used)) static inline int transaction_want_exec (transaction_t *T) {
  if (T->status == ts_running) {
    return 0;
  }
  if (T->status == ts_decryption_failed) {
    return 1;
  }

  if (T->status == ts_cancelled) {
    if (T->mask & MASK_RERUN_TRANSACTION) {
      return 1;
    }
    if (T->result == (((int) SIGINT) << 8) || T->result == (((int) SIGTERM) << 8)) {
      return 1;
    }
    return 0;
  }

  return (T->status == ts_interrupted) && (T->mask & MASK_RERUN_TRANSACTION);
}