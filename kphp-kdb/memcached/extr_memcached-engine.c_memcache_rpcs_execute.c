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
struct tl_query_header {int op; scalar_t__ actor_id; int /*<<< orphan*/  qid; } ;
struct connection {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int RPC_INVOKE_REQ ; 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  TL_ERROR_UNKNOWN ; 
 int /*<<< orphan*/  TL_ERROR_UNKNOWN_FUNCTION_ID ; 
#define  TL_MEMCACHE_ADD 134 
#define  TL_MEMCACHE_DECR 133 
#define  TL_MEMCACHE_DELETE 132 
#define  TL_MEMCACHE_GET 131 
#define  TL_MEMCACHE_INCR 130 
#define  TL_MEMCACHE_REPLACE 129 
#define  TL_MEMCACHE_SET 128 
 scalar_t__ advance_skip_read_ptr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mct_add ; 
 int /*<<< orphan*/  mct_replace ; 
 int /*<<< orphan*/  mct_set ; 
 scalar_t__ tl_fetch_error () ; 
 int /*<<< orphan*/  tl_fetch_init (struct connection*,int) ; 
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_query_header (struct tl_query_header*) ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ tl_fetch_unread () ; 
 int tl_memcache_delete () ; 
 int tl_memcache_get () ; 
 int tl_memcache_incr (int) ; 
 int tl_memcache_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int /*<<< orphan*/  tl_store_init_keep_error (struct connection*,int /*<<< orphan*/ ) ; 

int memcache_rpcs_execute (struct connection *c, int op, int len) {
  if (op != RPC_INVOKE_REQ) {
    return SKIP_ALL_BYTES;
  }
  tl_fetch_init (c, len - 4);
  struct tl_query_header h;
  tl_fetch_query_header (&h);
  tl_store_init_keep_error (c, h.qid);
  assert (h.op == op || tl_fetch_error ());

  if (h.actor_id) {
    tl_fetch_set_error ("Memcached only support actor_id = 0", 0);
  }

  int f = tl_fetch_int ();
  int result = -1;

  switch (f) {
  case TL_MEMCACHE_SET:
    result = tl_memcache_store (mct_set);
    break;
  case TL_MEMCACHE_ADD:
    result = tl_memcache_store (mct_add);
    break;
  case TL_MEMCACHE_REPLACE:
    result = tl_memcache_store (mct_replace);
    break;
  case TL_MEMCACHE_INCR:
    result = tl_memcache_incr (0);
    break;
  case TL_MEMCACHE_DECR:
    result = tl_memcache_incr (1);
    break;
  case TL_MEMCACHE_DELETE:
    result = tl_memcache_delete ();
    break;
  case TL_MEMCACHE_GET:
    result = tl_memcache_get ();
    break;
  default:
    tl_fetch_set_error_format (TL_ERROR_UNKNOWN_FUNCTION_ID, "Unknown function id 0x%08x", f);
  }

  if (result < 0) {
    tl_fetch_set_error ("Unknown error occured", TL_ERROR_UNKNOWN);
  }
  tl_store_end ();
  assert (advance_skip_read_ptr (&c->In, 4 + tl_fetch_unread ()) == 4 + tl_fetch_unread ());
  return 0;

}