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
struct tl_query_header {int op; long long actor_id; int flags; scalar_t__ string_forward_keys_pos; scalar_t__ string_forward_keys_num; scalar_t__ int_forward_keys_pos; scalar_t__ int_forward_keys_num; long long wait_binlog_pos; long long* int_forward_keys; long long int_forward; long long wait_binlog_time; long long binlog_pos; long long binlog_time; int /*<<< orphan*/  custom_timeout; int /*<<< orphan*/  string_forward; int /*<<< orphan*/ * string_forward_keys; int /*<<< orphan*/  kitten_php_delay; int /*<<< orphan*/  invoke_kphp_req_extra; } ;

/* Variables and functions */
 int RPC_DEST_ACTOR ; 
 int /*<<< orphan*/  RPC_DEST_ACTOR_FLAGS ; 
 scalar_t__ RPC_INVOKE_KPHP_REQ ; 
 scalar_t__ RPC_INVOKE_REQ ; 
 int RPC_REQ_ERROR ; 
 int RPC_REQ_ERROR_WRAPPED ; 
 int RPC_REQ_RESULT ; 
 int /*<<< orphan*/  RPC_REQ_RESULT_FLAGS ; 
 long long TL_OUT_QID ; 
 int TL_QUERY_HEADER_FLAG_CUSTOM_TIMEOUT ; 
 int TL_QUERY_HEADER_FLAG_INT_FORWARD ; 
 int TL_QUERY_HEADER_FLAG_INT_FORWARD_KEYS ; 
 int TL_QUERY_HEADER_FLAG_KPHP_DELAY ; 
 int TL_QUERY_HEADER_FLAG_STRING_FORWARD ; 
 int TL_QUERY_HEADER_FLAG_STRING_FORWARD_KEYS ; 
 int TL_QUERY_HEADER_FLAG_WAIT_BINLOG ; 
 int TL_QUERY_HEADER_FLAG_WAIT_BINLOG_TIME ; 
 int TL_QUERY_RESULT_HEADER_FLAG_BINLOG_POS ; 
 int TL_QUERY_RESULT_HEADER_FLAG_BINLOG_TIME ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int tl_write_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int tl_write_header (struct tl_query_header *header, int *buf, int size) {
  int _size = size;
  assert (header->op == (int)RPC_REQ_ERROR || header->op == (int)RPC_REQ_RESULT || header->op == (int)RPC_INVOKE_REQ || header->op == (int)RPC_REQ_ERROR_WRAPPED || header->op == (int)RPC_INVOKE_KPHP_REQ);
  if (header->op == (int)RPC_INVOKE_REQ || header->op == (int)RPC_INVOKE_KPHP_REQ) {
    if (header->op == (int)RPC_INVOKE_KPHP_REQ) {
      if (size < 24) { return -1; }
      memcpy (buf, header->invoke_kphp_req_extra, 24);
      buf += 24;
      size -= 24;
    }
    if (header->actor_id || header->flags) {
      if (header->flags) {
        if ((header->flags & TL_QUERY_HEADER_FLAG_STRING_FORWARD_KEYS) && header->string_forward_keys_pos >= header->string_forward_keys_num) {
          header->flags &= ~TL_QUERY_HEADER_FLAG_STRING_FORWARD_KEYS;
        }
        if ((header->flags & TL_QUERY_HEADER_FLAG_INT_FORWARD_KEYS) && header->int_forward_keys_pos >= header->int_forward_keys_num) {
          header->flags &= ~TL_QUERY_HEADER_FLAG_INT_FORWARD_KEYS;
        }
        if (size < 16) { return -1; }
        *(buf ++) = RPC_DEST_ACTOR_FLAGS;
        *(long long *)buf = header->actor_id;
        buf += 2;
        *(buf ++) = header->flags;
        size -= 16;
        if (header->flags & TL_QUERY_HEADER_FLAG_WAIT_BINLOG) {
          if (size < 8) { return -1; }
          *(long long *)buf = header->wait_binlog_pos;
          buf += 2;
          size -= 8;
        }
        if (header->flags & TL_QUERY_HEADER_FLAG_KPHP_DELAY) {
          if (size < 4) { return -1; }
          *(buf ++) = header->kitten_php_delay;
          size -= 4;
        }
        if (header->flags & TL_QUERY_HEADER_FLAG_STRING_FORWARD_KEYS) {
          if (size < 4) { return -1; }
          *(buf ++) = header->string_forward_keys_num - header->string_forward_keys_pos;
          size -= 4;
          int i;
          for (i = header->string_forward_keys_pos; i < header->string_forward_keys_num; i++) {
            int t = tl_write_string (header->string_forward_keys[i], strlen (header->string_forward_keys[i]), (char *)buf, size);
            if (t < 0) { return t; }
            buf += (t / 4);
            size -= t;
          }
        }
        if (header->flags & TL_QUERY_HEADER_FLAG_INT_FORWARD_KEYS) {
          if (size < 4) { return -1; }
          *(buf ++) = header->int_forward_keys_num - header->int_forward_keys_pos;
          size -= 4;
          int i;
          for (i = header->int_forward_keys_pos; i < header->int_forward_keys_num; i++) {
            if (size < 8) { return -1; }
            *(long long *)buf = header->int_forward_keys[i];
            buf += 2;
            size -= 8;
          }
        }
        if (header->flags & TL_QUERY_HEADER_FLAG_STRING_FORWARD) {
          int t = tl_write_string (header->string_forward, strlen (header->string_forward), (char *)buf, size);
          if (t < 0) { return -1; }
          buf += (t / 4);
          size -= t;
        }
        if (header->flags & TL_QUERY_HEADER_FLAG_INT_FORWARD) {
          if (size < 8) { return -1; }
          *(long long *)buf = header->int_forward;
          buf += 2;
          size -= 8;
        }
        if (header->flags & TL_QUERY_HEADER_FLAG_WAIT_BINLOG_TIME) {
          if (size < 8) { return -1; }
          *(long long *)buf = header->wait_binlog_time;
          buf += 2;
          size -= 8;
        }
        if (header->flags & TL_QUERY_HEADER_FLAG_CUSTOM_TIMEOUT) {
          if (size < 4) { return -1; }
          *(buf ++) = header->custom_timeout;
          size -= 4;
        }
        return _size - size;
      } else {
        if (size < 12) { return -1; }
        buf[0] = RPC_DEST_ACTOR;
        *(long long *)(buf + 1) = header->actor_id;
        return 12;
      }
    } else {
      return 0;
    }
  } else if (header->op == RPC_REQ_ERROR_WRAPPED) {
    if (size < 12) {
      return -1;
    }
    buf[0] = RPC_REQ_ERROR;
    *(long long *)(buf + 1) = TL_OUT_QID;
    return 12;
  } else if (header->op == RPC_REQ_RESULT) {
    if (header->flags) {
      if (size < 32) { return -1; }
      *(buf ++) = RPC_REQ_RESULT_FLAGS;
      *(buf ++) = header->flags;
      size -= 8;
      if (header->flags & TL_QUERY_RESULT_HEADER_FLAG_BINLOG_POS) {
        *(long long *)buf = header->binlog_pos;
        buf += 2;
        size -= 8;
      }
      if (header->flags & TL_QUERY_RESULT_HEADER_FLAG_BINLOG_TIME) {
        *(long long *)buf = header->binlog_time;
        buf += 2;
        size -= 8;
      }
      return _size - size; 
    }
    return 0;
  } else if (header->op == RPC_REQ_ERROR) {
    return 0;
  }
  return 0;
}