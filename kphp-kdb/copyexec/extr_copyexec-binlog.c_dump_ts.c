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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  out ; 
#define  ts_cancelled 135 
#define  ts_decryption_failed 134 
#define  ts_failed 133 
#define  ts_ignored 132 
#define  ts_interrupted 131 
#define  ts_io_failed 130 
#define  ts_running 129 
#define  ts_terminated 128 

__attribute__((used)) static void dump_ts (int tp) {
  switch (tp & 255) {
    case ts_running:
      fprintf (out, "running");
      break;
    case ts_ignored:
      fprintf (out, "ignored");
      break;
    case ts_interrupted:
      fprintf (out, "interrupted");
      break;
    case ts_cancelled:
      fprintf (out, "cancelled");
      break;
    case ts_terminated:
      fprintf (out, "terminated");
      break;
    case ts_failed:
      fprintf (out, "failed");
      break;
    case ts_decryption_failed:
      fprintf (out, "decryption_failed");
      break;
    case ts_io_failed:
      fprintf (out, "io_failed");
      break;
    default:
      fprintf (out, "%d", tp);
  }
}