#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mcc_data {int key_len; int arg_num; int response_len; int response_flags; int* args; int key_offset; } ;
struct TYPE_2__ {int total_bytes; } ;
struct connection {scalar_t__ generation; int unreliability; int fd; int remote_port; struct conn_query* first_query; int /*<<< orphan*/  ready; int /*<<< orphan*/  remote_ip; TYPE_1__ In; int /*<<< orphan*/  Q; int /*<<< orphan*/  last_response_time; } ;
struct conn_query {scalar_t__ req_generation; int custom_type; scalar_t__ extra; struct connection* requester; } ;
typedef  int /*<<< orphan*/  nb_iterator_t ;

/* Variables and functions */
 int MAX_KEY_LEN ; 
 unsigned int MAX_VALUE_LEN ; 
 struct mcc_data* MCC_DATA (struct connection*) ; 
 scalar_t__ MERGE_EXTENSION ; 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  client_errors_received ; 
 char* conv_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cr_failed ; 
 int /*<<< orphan*/  dump_connection_buffers (struct connection*) ; 
 int errors_received ; 
 int /*<<< orphan*/  fail_connection (struct connection*,int) ; 
 int /*<<< orphan*/  forward_response (struct connection*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
#define  mcrt_CLIENT_ERROR 139 
#define  mcrt_DELETED 138 
#define  mcrt_END 137 
#define  mcrt_ERROR 136 
#define  mcrt_NOTFOUND 135 
#define  mcrt_NOTSTORED 134 
#define  mcrt_NUMBER 133 
#define  mcrt_SERVER_ERROR 132 
#define  mcrt_STORED 131 
#define  mcrt_VALUE 130 
#define  mcrt_VERSION 129 
#define  mcrt_empty 128 
 int mct_add ; 
 int mct_decr ; 
 int mct_delete ; 
 int mct_get ; 
 int mct_incr ; 
 int mct_replace ; 
 int mct_set ; 
 int nbit_advance (int /*<<< orphan*/ *,int) ; 
 char* nbit_get_ptr (int /*<<< orphan*/ *) ; 
 int nbit_read_in (int /*<<< orphan*/ *,char*,int) ; 
 int nbit_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  precise_now ; 
 int /*<<< orphan*/  query_complete (struct connection*,int) ; 
 int search_check (int,char*,int) ; 
 int /*<<< orphan*/  search_merge (struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_skip (struct connection*,struct conn_query*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tot_skipped_answers ; 
 int verbosity ; 

int proxy_client_execute (struct connection *c, int op) {
  struct mcc_data *D = MCC_DATA(c);
  int len, x = 0;
  char *ptr;

  int get_allows_stored = 0, ignore_response = 0;
  
  if (verbosity > 0) {
    fprintf (stderr, "proxy_mc_client: op=%d, key_len=%d, arg#=%d, response_len=%d\n", op, D->key_len, D->arg_num, D->response_len);
  }

  if (c->first_query == (struct conn_query *)c && op != mcrt_empty && op != mcrt_VERSION) {
    if (verbosity >= 0) {
      fprintf (stderr, "response received for empty query list? op=%d\n", op);
      if (verbosity > -2) {
        dump_connection_buffers (c);
        if (c->first_query != (struct conn_query *) c && c->first_query->req_generation == c->first_query->requester->generation) {
          dump_connection_buffers (c->first_query->requester);
        }
      }
    }
    D->response_flags |= 16;
    return SKIP_ALL_BYTES;
  }

  if (c->first_query != (struct conn_query *) c && op != mcrt_empty && op != mcrt_VERSION) {
    get_allows_stored = c->first_query->custom_type & 0x1000;
    ignore_response = c->first_query->custom_type & 0x2000;
    c->first_query->custom_type &= 0xfff;
  }

  c->last_response_time = precise_now;

  switch (op) {

  case mcrt_empty:
    return SKIP_ALL_BYTES;

  case mcrt_VALUE:

    if (D->key_len > 0 && D->key_len <= MAX_KEY_LEN && D->arg_num == 2 && (unsigned) D->args[1] <= MAX_VALUE_LEN) {
      int needed_bytes = D->args[1] + D->response_len + 2 - c->In.total_bytes;
      if (needed_bytes > 0) {
        return needed_bytes;
      }
      nbit_advance (&c->Q, D->args[1]);
      len = nbit_ready_bytes (&c->Q);
      assert (len > 0);
      ptr = nbit_get_ptr (&c->Q);
    } else {
      fprintf (stderr, "error at VALUE: op=%d, key_len=%d, arg_num=%d, value_len=%lld\n", op, D->key_len, D->arg_num, D->args[1]);
     
      if (verbosity > -2) {
        dump_connection_buffers (c);
        if (c->first_query != (struct conn_query *) c && c->first_query->req_generation == c->first_query->requester->generation) {
          dump_connection_buffers (c->first_query->requester);
        }
      }

      D->response_flags |= 16;
      return SKIP_ALL_BYTES;
    }
    if (len == 1) {
      nbit_advance (&c->Q, 1);
    }
    if (ptr[0] != '\r' || (len > 1 ? ptr[1] : *((char *) nbit_get_ptr(&c->Q))) != '\n') {
      fprintf (stderr, "missing cr/lf at VALUE: op=%d, key_len=%d, arg_num=%d, value_len=%lld\n", op, D->key_len, D->arg_num, D->args[1]);

      if (verbosity > -2) {
        dump_connection_buffers (c);
        if (c->first_query != (struct conn_query *) c && c->first_query->req_generation == c->first_query->requester->generation) {
          dump_connection_buffers (c->first_query->requester);
        }
      }

      D->response_flags |= 16;
      return SKIP_ALL_BYTES;
    }
    len = 2;

    if (verbosity > 0) {
      fprintf (stderr, "mcc_value: op=%d, key_len=%d, flags=%lld, time=%lld, value_len=%lld\n", op, D->key_len, D->args[0], D->args[1], D->args[2]);
    }

    if (c->first_query->custom_type != mct_get || get_allows_stored) {
      fprintf (stderr, "VALUE obtained for a non-get query: op=%d, query_type=%d, key_len=%d, arg_num=%d, value_len=%lld, get_allows_stored=%d\n", op, c->first_query->custom_type, D->key_len, D->arg_num, D->args[1], get_allows_stored);
      D->response_flags |= 16;
      return SKIP_ALL_BYTES;
    }

    int search_mode = 0;
#ifdef SEARCH_MODE_ENABLED
    if (MERGE_EXTENSION) {
      static char buff[1024];
      nb_iterator_t R;
      nbit_set (&R, &c->In);
      assert (nbit_advance (&R, D->key_offset) == D->key_offset);
      int l = nbit_read_in (&R, buff, 1023);
      buff[l] = 0;
      search_mode = search_check (mct_get, buff, l);
    }
#endif
    if (!search_mode) {
      forward_response (c, D->response_len + D->args[1] + len);
    } else {
#ifdef SEARCH_MODE_ENABLED
      search_merge (c, D->response_len + D->args[1] + len);
#else 
      assert (0);
#endif
    }

    return 0;

  case mcrt_VERSION:

    c->unreliability >>= 1;
    if (verbosity > 0) {
      fprintf (stderr, "mcc_got_version: op=%d, key_len=%d, unreliability=%d\n", op, D->key_len, c->unreliability);
    }

    return SKIP_ALL_BYTES;

  case mcrt_CLIENT_ERROR:
    fprintf (stderr, "CLIENT_ERROR received from connection %d (%s:%d)\n", c->fd, conv_addr (c->remote_ip, 0), c->remote_port);
    client_errors_received++;
  case mcrt_ERROR:
    errors_received++;
    if (verbosity > -2 && errors_received < 32) {
      dump_connection_buffers (c);
      if (c->first_query != (struct conn_query *) c && c->first_query->req_generation == c->first_query->requester->generation) {
        dump_connection_buffers (c->first_query->requester);
      }
    }
    fail_connection (c, -5);
    c->ready = cr_failed;
    return SKIP_ALL_BYTES;
  case mcrt_SERVER_ERROR:
    x = -1 & (~(1 << mct_get));
    break;

  case mcrt_NUMBER:
    x = (1 << mct_incr) | (1 << mct_decr);
    break;

  case mcrt_STORED:
  case mcrt_NOTSTORED:
    x = (1 << mct_set) | (1 << mct_add) | (1 << mct_replace);
    if (get_allows_stored) {
      x |= (1 << mct_get);
    }
    break;

  case mcrt_DELETED:
    x = 1 << mct_delete;
    break;

  case mcrt_NOTFOUND:
    x = (1 << mct_delete) | (1 << mct_incr) | (1 << mct_decr);
    break;

  case mcrt_END:
    x = 1 << mct_get;
    break;

  default:
    x = 0;
  }

#ifdef SEARCH_MODE_ENABLED
  if (MERGE_EXTENSION && op == mcrt_END) {
    while (c->first_query != (struct conn_query *)c) {
      struct conn_query *q = c->first_query;
      if (q->extra) {
        if (verbosity > 1) {
          fprintf (stderr, "Deleting unanswered search query %p\n", q);
        }
        search_skip (c, q);
        //query_complete (c, 1);
      } else {
        break;
      }
    }
    assert (c->first_query != (struct conn_query *)c);
  }
#endif

  if (D->key_len || D->arg_num != (op == mcrt_NUMBER) || ((1 << c->first_query->custom_type) & x) == 0) {
    fprintf (stderr, "INCORRECT response obtained for a query: op=%d, query_type=%d, key_len=%d, arg_num=%d, allowed_mask=%d\n", op, c->first_query->custom_type, D->key_len, D->arg_num, x);
    D->response_flags |= 16;
    return SKIP_ALL_BYTES;
  }

  if (verbosity > 0) {
    fprintf (stderr, "mcc_op: op=%d, key_len=%d, arg=%lld\n", op, D->key_len, D->args[0]);
  }

  if (c->first_query->custom_type == mct_get && (op == mcrt_STORED || op == mcrt_NOTSTORED)) {
    if (verbosity > 1) {
      fprintf (stderr, "STORED/NOT_STORED response for get, skipping\n");
    }
    return SKIP_ALL_BYTES;
  }

  if (ignore_response) {
    if (verbosity > 1) {
      fprintf (stderr, "STORED/NOT_STORED/DELETED/... response (%d) for immediate/diagonal distribution query, skipping\n", op);
    }
    ++tot_skipped_answers;
    query_complete (c, 1);
    return SKIP_ALL_BYTES;
  }

  if (c->first_query->custom_type == mct_get || op == mcrt_END) {
    query_complete (c, op == mcrt_END);
    return SKIP_ALL_BYTES;
  }

  forward_response (c, D->response_len);
  query_complete (c, 1);

  return 0;
}