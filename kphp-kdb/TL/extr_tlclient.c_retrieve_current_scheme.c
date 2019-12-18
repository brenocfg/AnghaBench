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
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  log_printf (char*,char*) ; 
 int /*<<< orphan*/ * scheme_filename ; 
 scalar_t__ send_rpc_command (char*) ; 

int retrieve_current_scheme (char *s) {
  scheme_filename = fopen (s, "w");
  if (scheme_filename == NULL) {
    log_printf ("Couln't open \"%s\" for writing. %m\n", s);
    return -1;
  }

  if (send_rpc_command ("(help.getScheme 1)") < 0) {
    return -1;
  }
  return 0;
}