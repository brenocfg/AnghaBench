#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_rpc_fetch_eof (scalar_t__*) ; 
 TYPE_1__ tl ; 
 int /*<<< orphan*/  tl_set_error (char*) ; 

void tl_parse_end (void) {
  if (tl.error) { return; }
  if (!do_rpc_fetch_eof (&tl.error)) {
    tl_set_error ("Extra data");
  }
}