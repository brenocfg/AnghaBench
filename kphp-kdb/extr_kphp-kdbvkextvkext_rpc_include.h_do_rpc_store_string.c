#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_BUFFER_MAGIC ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_write_string (TYPE_1__*,int,char const*) ; 
 int /*<<< orphan*/  buffer_write_string_tiny (TYPE_1__*,int,char const*) ; 
 TYPE_1__* outbuf ; 
 int /*<<< orphan*/  store ; 

__attribute__((used)) static void do_rpc_store_string (const char *s, int len) { /* {{{ */
  ADD_CNT (store);
  START_TIMER (store);
  assert (len <= 0xffffff);
  assert (outbuf && outbuf->magic == RPC_BUFFER_MAGIC);
  if (len <= 253) {
    buffer_write_string_tiny (outbuf, len, s);
  } else {
    buffer_write_string (outbuf, len, s);
  }
#ifdef STORE_DEBUG
  fprintf (stderr, "%.*s\n", len, s);
#endif
  END_TIMER (store);
}