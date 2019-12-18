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
struct TYPE_2__ {scalar_t__ magic; scalar_t__ rptr; scalar_t__ wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_BUFFER_MAGIC ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fetch ; 
 TYPE_1__* inbuf ; 

int do_rpc_fetch_eof (char **error) { /* {{{ */
  ADD_CNT (fetch);
  START_TIMER (fetch);
  if (!inbuf) {
    *error = "Trying fetch from empty buffer\n";
    END_TIMER (fetch);
    return 0;
  }
  assert (inbuf->magic == RPC_BUFFER_MAGIC);
  if (inbuf->rptr < inbuf->wptr) {
    *error = 0;
    END_TIMER (fetch);
    return 0;
  } else {
    *error = 0;
    END_TIMER (fetch);
    return 1;
  }
}