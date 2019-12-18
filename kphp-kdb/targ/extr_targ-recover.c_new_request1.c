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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_connection_output (struct connection*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ max_ad_id ; 
 scalar_t__ next_ad_id ; 
 int sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

void new_request1 (struct connection *c) {
  if (next_ad_id > max_ad_id) {
    if (verbosity > 0) {
      fprintf (stderr, "%d ads complete, exiting\n", max_ad_id);
    }
    exit (0);
  }
  static char buff[256];
  int len = sprintf (buff, "get ad_info%d\r\n", next_ad_id);
  write_out (&c->Out, buff, len);
  flush_connection_output (c);
  if (verbosity > 1) {
    fprintf (stderr, "Requested information about ad %d\n", next_ad_id);
  }
}