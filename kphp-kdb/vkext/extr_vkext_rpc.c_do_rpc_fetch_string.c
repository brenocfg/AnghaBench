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
 scalar_t__ buffer_read_string (TYPE_1__*,int*,char**) ; 
 int /*<<< orphan*/  fetch ; 
 TYPE_1__* inbuf ; 
 char* strdup (char*) ; 

int do_rpc_fetch_string (char **value) { /* {{{ */
  ADD_CNT (fetch);
  START_TIMER (fetch);
  if (!inbuf) {
    *value = strdup ("Trying fetch from empty buffer\n");
    END_TIMER (fetch);
    return -1;
  }
  assert (inbuf->magic == RPC_BUFFER_MAGIC);
  int value_len;
  if (buffer_read_string (inbuf, &value_len, value) < 0) {
    *value = strdup ("Can not fetch string from inbuf\n");
    END_TIMER (fetch);
    return -1;
  } else {
    END_TIMER (fetch);
    return value_len;
  }
}