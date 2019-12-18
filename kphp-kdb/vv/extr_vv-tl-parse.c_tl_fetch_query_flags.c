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
struct tl_query_header {int flags; int kitten_php_delay; int string_forward_keys_num; char** string_forward_keys; int int_forward_keys_num; char* string_forward; int custom_timeout; void* wait_binlog_time; void* int_forward; void** int_forward_keys; void* wait_binlog_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_ERROR_HEADER ; 
 int TL_QUERY_HEADER_FLAG_CUSTOM_TIMEOUT ; 
 int TL_QUERY_HEADER_FLAG_INT_FORWARD ; 
 int TL_QUERY_HEADER_FLAG_INT_FORWARD_KEYS ; 
 int TL_QUERY_HEADER_FLAG_KPHP_DELAY ; 
 int TL_QUERY_HEADER_FLAG_MASK ; 
 int TL_QUERY_HEADER_FLAG_STRING_FORWARD ; 
 int TL_QUERY_HEADER_FLAG_STRING_FORWARD_KEYS ; 
 int TL_QUERY_HEADER_FLAG_WAIT_BINLOG ; 
 int TL_QUERY_HEADER_FLAG_WAIT_BINLOG_TIME ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ tl_fetch_error () ; 
 void* tl_fetch_int () ; 
 void* tl_fetch_long () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tl_fetch_string_data (char*,int) ; 
 int tl_fetch_string_len (int) ; 

int tl_fetch_query_flags (struct tl_query_header *header) {
  int flags = tl_fetch_int ();
  int i;
  if (tl_fetch_error ()) {
    return -1;
  }
  if (header->flags & flags) {
    tl_fetch_set_error_format (TL_ERROR_HEADER, "Duplicate flags in header 0x%08x", header->flags & flags);
    return -1;
  }
  if (flags & ~TL_QUERY_HEADER_FLAG_MASK) {
    tl_fetch_set_error_format (TL_ERROR_HEADER, "Unsupported flags in header 0x%08x", (~TL_QUERY_HEADER_FLAG_MASK) & flags);
    return -1;
  }
  header->flags |= flags;
  if (flags & TL_QUERY_HEADER_FLAG_WAIT_BINLOG) {
    header->wait_binlog_pos = tl_fetch_long ();
    if (tl_fetch_error ()) {
      return -1;
    }
  }
  if (flags & TL_QUERY_HEADER_FLAG_KPHP_DELAY) {
    header->kitten_php_delay = tl_fetch_int ();
    if (tl_fetch_error ()) {
      return -1;
    }
    if (header->kitten_php_delay < 0) {
      header->kitten_php_delay = 0;
    }
    if (header->kitten_php_delay > 120000) {
      header->kitten_php_delay = 120000;
    }
  }
  if (flags & TL_QUERY_HEADER_FLAG_STRING_FORWARD_KEYS) {
    header->string_forward_keys_num = tl_fetch_int ();
    if (header->string_forward_keys_num < 0 || header->string_forward_keys_num > 10) {
      tl_fetch_set_error_format (TL_ERROR_HEADER, "Number of string forward keys should be in range 0..10. Value %d", header->string_forward_keys_num);
      return -1;
    }
    if (tl_fetch_error ()) {
      return -1;
    }
    for (i = 0; i < header->string_forward_keys_num; i++) {
      int l = tl_fetch_string_len (1000);
      if (tl_fetch_error ()) {
        return -1;
      }
      header->string_forward_keys[i] = (char *)malloc (l + 1);
      tl_fetch_string_data (header->string_forward_keys[i], l);
      header->string_forward_keys[i][l] = 0;
      if (tl_fetch_error ()) {
        return -1;
      }
    }
  }
  if (flags & TL_QUERY_HEADER_FLAG_INT_FORWARD_KEYS) {
    header->int_forward_keys_num = tl_fetch_int ();
    if (header->int_forward_keys_num < 0 || header->int_forward_keys_num > 10) {
      tl_fetch_set_error_format (TL_ERROR_HEADER, "Number of int forward keys should be in range 0..10. Value %d", header->int_forward_keys_num);
      return -1;
    }
    if (tl_fetch_error ()) {
      return -1;
    }
    for (i = 0; i < header->int_forward_keys_num; i++) {
      header->int_forward_keys[i] = tl_fetch_long ();
      if (tl_fetch_error ()) {
        return -1;
      }
    }
  }
  if (flags & TL_QUERY_HEADER_FLAG_STRING_FORWARD) {
    int l = tl_fetch_string_len (1000);
    if (tl_fetch_error ()) {
      return -1;
    }
    header->string_forward = (char *)malloc (l + 1);
    tl_fetch_string_data (header->string_forward, l);
    header->string_forward[l] = 0;
    if (tl_fetch_error ()) {
      return -1;
    }
  }
  if (flags & TL_QUERY_HEADER_FLAG_INT_FORWARD) {
    header->int_forward = tl_fetch_long ();
    if (tl_fetch_error ()) {
      return -1;
    }
  }
  if (flags & TL_QUERY_HEADER_FLAG_WAIT_BINLOG_TIME) {
    header->wait_binlog_time = tl_fetch_long ();
    if (tl_fetch_error ()) {
      return -1;
    }
  }
  if (flags & TL_QUERY_HEADER_FLAG_CUSTOM_TIMEOUT) {
    header->custom_timeout = tl_fetch_int ();
    if (tl_fetch_error ()) {
      return -1;
    }
    if (header->custom_timeout < 0) {
      header->custom_timeout = 0;
    }
    if (header->custom_timeout > 120000) {
      header->custom_timeout = 120000;
    }
  }
  return 0;
}