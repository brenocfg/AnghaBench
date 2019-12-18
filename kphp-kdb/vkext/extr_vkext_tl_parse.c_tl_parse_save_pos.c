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
 int do_rpc_fetch_get_pos (char**) ; 
 int /*<<< orphan*/  tl_set_error (char*) ; 

int tl_parse_save_pos (void) {
  char *error = 0;
  int r = do_rpc_fetch_get_pos (&error);
  if (error) {
    tl_set_error (error);
    return 0;
  } else {
    return r;
  }
}