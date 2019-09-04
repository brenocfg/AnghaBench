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
struct tl_query_header {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int RPC_REQ_RESULT_FLAGS ; 
 int TL_QUERY_HEADER_FLAG_RETURN_BINLOG_POS ; 
 int TL_QUERY_HEADER_FLAG_RETURN_BINLOG_TIME ; 
 long long get_precise_time (int) ; 
 long long log_last_pos () ; 
 int tl_result_new_flags (int /*<<< orphan*/ ) ; 

int tl_result_make_header (int *ptr, struct tl_query_header *h) {
  int *p = ptr;
  if (!h->flags) { return 0; }
  int new_flags = tl_result_new_flags (h->flags);
  *p = RPC_REQ_RESULT_FLAGS; 
  p++;
  *p = new_flags;
  p ++;
  if (new_flags & TL_QUERY_HEADER_FLAG_RETURN_BINLOG_POS) {
    *(long long *)p = log_last_pos ();
    p += 2;
  }
  if (new_flags & TL_QUERY_HEADER_FLAG_RETURN_BINLOG_TIME) {
    *(long long *)p = get_precise_time (1000000);
    p += 2;
  }
  return (p - ptr) * 4;
}