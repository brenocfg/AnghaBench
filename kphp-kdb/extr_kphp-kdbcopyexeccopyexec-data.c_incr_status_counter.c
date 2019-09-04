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
typedef  enum transaction_status { ____Placeholder_transaction_status } transaction_status ;

/* Variables and functions */
 int tot_cancelled ; 
 int tot_decryption_failed ; 
 int tot_failed ; 
 int tot_ignored ; 
 int tot_interrupted ; 
 int tot_io_failed ; 
 int tot_terminated ; 
#define  ts_cancelled 134 
#define  ts_decryption_failed 133 
#define  ts_failed 132 
#define  ts_ignored 131 
#define  ts_interrupted 130 
#define  ts_io_failed 129 
#define  ts_terminated 128 

__attribute__((used)) static void incr_status_counter (enum transaction_status status, int delta) {
  switch (status) {
    case ts_ignored:
      tot_ignored += delta;
      break;
    case ts_interrupted:
      tot_interrupted += delta;
      break;
    case ts_cancelled:
      tot_cancelled += delta;
      break;
    case ts_terminated:
      tot_terminated += delta;
      break;
    case ts_failed:
      tot_failed += delta;
      break;
    case ts_decryption_failed:
      tot_decryption_failed += delta;
      break;
    case ts_io_failed:
      tot_io_failed += delta;
      break;
    default:
      break;
  }
}