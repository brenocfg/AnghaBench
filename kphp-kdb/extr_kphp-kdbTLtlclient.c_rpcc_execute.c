#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tl_scheme_object {int dummy; } ;
struct connection {int /*<<< orphan*/  In; } ;
struct TYPE_7__ {int tabsize; int /*<<< orphan*/  indentation; } ;
struct TYPE_6__ {char* buff; } ;

/* Variables and functions */
 long long* P ; 
 int PACKET_BUFFER_SIZE ; 
 int RPC_REQ_ERROR ; 
 int RPC_REQ_RESULT ; 
 int SKIP_ALL_BYTES ; 
 int TL_SECTION_TYPES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compiler ; 
 int /*<<< orphan*/  cstr_free (int /*<<< orphan*/ *) ; 
 int expect_input ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* get_raw_scheme (struct tl_scheme_object*) ; 
 int /*<<< orphan*/  kprintf (char*,long long,long long) ; 
 int /*<<< orphan*/  log_char (char) ; 
 int /*<<< orphan*/  log_errors () ; 
 int /*<<< orphan*/  log_str (char*) ; 
 int /*<<< orphan*/  memcpy (long long*,...) ; 
 TYPE_5__ params ; 
 int read_in (int /*<<< orphan*/ *,long long*,int) ; 
 long long req_id ; 
 int /*<<< orphan*/  rpcc_log_error (int) ; 
 int /*<<< orphan*/ * scheme_filename ; 
 int /*<<< orphan*/  tl_compiler_clear_errors (int /*<<< orphan*/ *) ; 
 int tl_expression_unserialize (int /*<<< orphan*/ *,int*,int,int,int /*<<< orphan*/ ,struct tl_scheme_object**) ; 
 int /*<<< orphan*/  tl_scheme_object_free (struct tl_scheme_object*) ; 
 int /*<<< orphan*/  tl_string_buffer_append_char (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_string_buffer_clear (TYPE_1__*) ; 
 int tl_unserialize_rpc_function_result (int /*<<< orphan*/ *,TYPE_1__*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typename ; 
 scalar_t__ unpack_packet (int /*<<< orphan*/ *,int,int**,int*) ; 
 TYPE_1__ unserialize_buff ; 

int rpcc_execute (struct connection *c, int op, int len) {
  if (len > PACKET_BUFFER_SIZE) {
    return SKIP_ALL_BYTES;
  }
  if (op == RPC_REQ_RESULT) {
    long long r;
    assert (read_in (&c->In, P, len) == len);
    memcpy (&r, &P[3], 8);
    if (r != req_id) {
      kprintf ("RPC_REQ_RESULT: req_id = %lld, expected req_id = %lld\n", r, req_id);
      return 0;
    } else {
      int *Q;
      int qlen;
      tl_string_buffer_clear (&unserialize_buff);
      tl_compiler_clear_errors (&compiler);
      if (unpack_packet (&compiler, len, &Q, &qlen) < 0) {
        log_errors ();
        log_str ("unpack packet fail\n");
      } else {
        if (scheme_filename) {
          struct tl_scheme_object *O = NULL;
          tl_compiler_clear_errors (&compiler);
          int r = tl_expression_unserialize (&compiler, Q, qlen, 1 << TL_SECTION_TYPES, typename, &O);
          if (r >= 0 && O != NULL) {
            //tl_scheme_object_sbdump (b, O);
            char *s = get_raw_scheme (O);
            if (s) {
              fprintf (scheme_filename, "%s", s);
            }
            tl_scheme_object_free (O);
          }
          fclose (scheme_filename);
          scheme_filename = NULL;
        } else {
          if (qlen && Q[0] == RPC_REQ_ERROR) {
            int o = 4 * (qlen - 1);
            memcpy (P+5, Q+1, o);
            rpcc_log_error (o + 24);
            expect_input = 1;
            return 0;
          }
          int r = tl_unserialize_rpc_function_result (&compiler, &unserialize_buff, Q, qlen, typename, params.indentation);
          if (r < 0) {
            log_errors ();
          } else {
            if (r != qlen) {
              kprintf ("Warning: unserialize %d ints of result, but result contains %d ints.\n", r, qlen);
            }
            tl_string_buffer_append_char (&unserialize_buff, 0);
            char *s = unserialize_buff.buff;
            while (*s) {
              if (*s == '\t') {
                int k;
                for (k = 0; k < params.tabsize; k++) {
                  log_char (' ');
                }
              } else {
                log_char (*s);
              }
              s++;
            }
            log_char ('\n');
          }
        }
      }
      cstr_free (&typename);
      expect_input = 1;
    }
    return 0;
  } if (op == RPC_REQ_ERROR) {
    long long received_req_id;
    assert (read_in (&c->In, P, len) == len);
    memcpy (&received_req_id, &P[3], 8);
    if (received_req_id != req_id) {
      kprintf ("RPC_REQ_ERROR: req_id = %lld, expected req_id = %lld\n", received_req_id, req_id);
      return 0;
    } else {
      rpcc_log_error (len);
    }
    cstr_free (&typename);
    expect_input = 1;
    return 0;
  } else {
    return SKIP_ALL_BYTES;
  }
}