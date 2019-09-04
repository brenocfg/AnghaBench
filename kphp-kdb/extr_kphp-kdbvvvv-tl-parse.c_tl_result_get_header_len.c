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
 int TL_QUERY_HEADER_FLAG_RETURN_BINLOG_POS ; 
 int TL_QUERY_HEADER_FLAG_RETURN_BINLOG_TIME ; 
 int tl_result_new_flags (int /*<<< orphan*/ ) ; 

int tl_result_get_header_len (struct tl_query_header *h) {
  if (!h->flags) { return 0; }
  int new_flags = tl_result_new_flags (h->flags);
  int s = 8;
  if (new_flags & TL_QUERY_HEADER_FLAG_RETURN_BINLOG_POS) {
    s += 8;
  }
  if (new_flags & TL_QUERY_HEADER_FLAG_RETURN_BINLOG_TIME) {
    s += 8;
  }
  return s;
}