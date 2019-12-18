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
#define  ts_cancelled 135 
#define  ts_decryption_failed 134 
#define  ts_failed 133 
#define  ts_ignored 132 
#define  ts_interrupted 131 
#define  ts_io_failed 130 
#define  ts_running 129 
#define  ts_terminated 128 

__attribute__((used)) static char *status_to_alpha (int tp) {
  switch (tp) {
    case ts_running:
      return "running";
    case ts_ignored:
      return "ignored";
      break;
    case ts_interrupted:
      return "interrupted";
      break;
    case ts_cancelled:
      return "cancelled";
      break;
    case ts_terminated:
      return "terminated";
      break;
    case ts_failed:
      return "failed";
      break;
    case ts_decryption_failed:
      return "decryption_failed";
      break;
    case ts_io_failed:
      return "io_failed";
    default:
      return "unknown";
  }
}