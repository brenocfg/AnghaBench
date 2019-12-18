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
struct TYPE_2__ {scalar_t__ sptr; scalar_t__ wptr; scalar_t__ magic; scalar_t__ rptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_BUFFER_MAGIC ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fetch ; 
 TYPE_1__* inbuf ; 
 char* strdup (char*) ; 

int do_rpc_fetch_set_pos (int pos, char **error) { /* {{{ */
  ADD_CNT (fetch);
  START_TIMER (fetch);
  if (!inbuf) {
    *error = strdup ("Trying to fetch from empty buffer\n");
    END_TIMER (fetch);
    return 0;
  }
  if (pos < 0 || inbuf->sptr + pos > inbuf->wptr) {
    *error = strdup ("Trying to set bad position\n");
    END_TIMER (fetch);
    return 0;
  }
  assert (inbuf->magic == RPC_BUFFER_MAGIC);
  *error = 0;
  inbuf->rptr = inbuf->sptr + pos;
  END_TIMER (fetch);
  return 1;
}