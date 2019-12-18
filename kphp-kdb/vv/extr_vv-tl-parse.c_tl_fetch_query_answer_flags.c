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
struct tl_query_header {int flags; void* binlog_time; void* binlog_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_ERROR_HEADER ; 
 int TL_QUERY_RESULT_HEADER_FLAG_BINLOG_POS ; 
 int TL_QUERY_RESULT_HEADER_FLAG_BINLOG_TIME ; 
 int TL_QUERY_RESULT_HEADER_FLAG_MASK ; 
 scalar_t__ tl_fetch_error () ; 
 int tl_fetch_int () ; 
 void* tl_fetch_long () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int) ; 

int tl_fetch_query_answer_flags (struct tl_query_header *header) {
  int flags = tl_fetch_int ();
  if (tl_fetch_error ()) {
    return -1;
  }
  if (header->flags & flags) {
    tl_fetch_set_error_format (TL_ERROR_HEADER, "Duplicate flags in header 0x%08x", header->flags & flags);
    return -1;
  }
  if (flags & ~TL_QUERY_RESULT_HEADER_FLAG_MASK) {
    tl_fetch_set_error_format (TL_ERROR_HEADER, "Unsupported flags in header 0x%08x", (~TL_QUERY_RESULT_HEADER_FLAG_MASK) & flags);
    return -1;
  }
  header->flags |= flags;
  if (flags & TL_QUERY_RESULT_HEADER_FLAG_BINLOG_POS) {
    header->binlog_pos = tl_fetch_long ();
    if (tl_fetch_error ()) {
      return -1;
    }
  }
  if (flags & TL_QUERY_RESULT_HEADER_FLAG_BINLOG_TIME) {
    header->binlog_time = tl_fetch_long ();
    if (tl_fetch_error ()) {
      return -1;
    }
  }
  return 0;
}