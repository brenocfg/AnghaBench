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
struct TYPE_3__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_BUFFER_MAGIC ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ buffer_read_long (TYPE_1__*,long long*) ; 
 int /*<<< orphan*/  fetch ; 
 TYPE_1__* inbuf ; 
 char* strdup (char*) ; 

long long do_rpc_fetch_long (char **error) { /* {{{ */
  ADD_CNT (fetch);
  START_TIMER (fetch);
  if (!inbuf) {
    *error = strdup ("Trying to fetch from empty buffer\n");
    return 0;
  }
  assert (inbuf->magic == RPC_BUFFER_MAGIC);
  
  long long value;
  if (buffer_read_long (inbuf, &value) < 0) {
    *error = strdup ("Can not fetch long from inbuf");
    END_TIMER (fetch);
    return 0;
  } else {
    END_TIMER (fetch);
    *error = 0;
    return value;
  }
}