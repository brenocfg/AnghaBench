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
struct hts_data {scalar_t__ query_type; int data_size; int wlen; char* word; int query_words; int query_flags; long long uri_offset; long long header_size; int uri_size; long long host_offset; int host_size; long long first_line_size; int /*<<< orphan*/  http_ver; } ;
struct connection {scalar_t__ status; int parse_state; int /*<<< orphan*/  In; int /*<<< orphan*/  Q; scalar_t__ pending_queries; } ;
struct TYPE_2__ {int (* execute ) (struct connection*,scalar_t__) ;} ;

/* Variables and functions */
 struct hts_data* HTS_DATA (struct connection*) ; 
 TYPE_1__* HTS_FUNC (struct connection*) ; 
 int /*<<< orphan*/  HTTP_V09 ; 
 int /*<<< orphan*/  HTTP_V10 ; 
 int /*<<< orphan*/  HTTP_V11 ; 
 long long MAX_HTTP_HEADER_SIZE ; 
 int NEED_MORE_BYTES ; 
 int QF_CONNECTION ; 
 int QF_DATASIZE ; 
 int QF_ERROR ; 
 int QF_HOST ; 
 int QF_KEEPALIVE ; 
 int SKIP_ALL_BYTES ; 
 int advance_skip_read_ptr (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_expect_query ; 
 scalar_t__ conn_reading_query ; 
 scalar_t__ conn_running ; 
 scalar_t__ conn_wait_aio ; 
 scalar_t__ conn_wait_net ; 
 scalar_t__ conn_write_close ; 
#define  htqp_done 140 
#define  htqp_eoln 139 
#define  htqp_fatal 138 
#define  htqp_linestart 137 
#define  htqp_readint 136 
#define  htqp_readtocolon 135 
#define  htqp_readtospace 134 
#define  htqp_skipspc 133 
#define  htqp_skipspctoeoln 132 
#define  htqp_skiptoeoln 131 
#define  htqp_start 130 
#define  htqp_wantlastlf 129 
#define  htqp_wantlf 128 
 scalar_t__ htqt_error ; 
 scalar_t__ htqt_get ; 
 scalar_t__ htqt_head ; 
 scalar_t__ htqt_none ; 
 scalar_t__ htqt_post ; 
 int hts_default_execute (struct connection*,scalar_t__) ; 
 int /*<<< orphan*/  http_bad_headers ; 
 int /*<<< orphan*/  http_queries ; 
 int /*<<< orphan*/  http_queries_size ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct hts_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nbit_advance (int /*<<< orphan*/ *,int) ; 
 char* nbit_get_ptr (int /*<<< orphan*/ *) ; 
 int nbit_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int stub1 (struct connection*,scalar_t__) ; 
 int /*<<< orphan*/  write_http_error (struct connection*,int) ; 

int hts_parse_execute (struct connection *c) {
  struct hts_data *D = HTS_DATA(c);
  char *ptr, *ptr_s, *ptr_e;
  int len;
  long long tt;

  while (c->status == conn_expect_query || c->status == conn_reading_query) {
    len = nbit_ready_bytes (&c->Q);
    ptr = ptr_s = nbit_get_ptr (&c->Q);
    ptr_e = ptr + len;
    if (len <= 0) {
      break;
    }

    while (ptr < ptr_e && c->parse_state != htqp_done) {

      switch (c->parse_state) {
        case htqp_start:
          //fprintf (stderr, "htqp_start: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);
          memset (D, 0, sizeof (*D));
          D->query_type = htqt_none;
          D->data_size = -1;
          c->parse_state = htqp_readtospace;

        case htqp_readtospace:
          //fprintf (stderr, "htqp_readtospace: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);
          while (ptr < ptr_e && ((unsigned) *ptr > ' ')) {
            if (D->wlen < 15) {
              D->word[D->wlen] = *ptr;
            }
            D->wlen++;
            ptr++;
          }
          if (D->wlen > 4096) {
            c->parse_state = htqp_fatal;
            break;
          }
          if (ptr == ptr_e) {
            break;
          }
          c->parse_state = htqp_skipspc;
          D->query_words++;
          if (D->query_words == 1) {
            D->query_type = htqt_error;
            if (D->wlen == 3 && !memcmp (D->word, "GET", 3)) {
              D->query_type = htqt_get;
            } else if (D->wlen == 4) {
              if (!memcmp (D->word, "HEAD", 4)) {
                D->query_type = htqt_head;
              } else if (!memcmp (D->word, "POST", 4)) {
                D->query_type = htqt_post;
              }
            }
            if (D->query_type == htqt_error) {
              c->parse_state = htqp_skiptoeoln;
              D->query_flags |= QF_ERROR;
            }
          } else if (D->query_words == 2) {
            D->uri_offset = D->header_size;
            D->uri_size = D->wlen;
            if (!D->wlen) {
              c->parse_state = htqp_skiptoeoln;
              D->query_flags |= QF_ERROR;
            }
          } else if (D->query_words == 3) {
            c->parse_state = htqp_skipspctoeoln;
            if (D->wlen != 0) {
              /* HTTP/x.y */
              if (D->wlen != 8) {
                c->parse_state = htqp_skiptoeoln;
                D->query_flags |= QF_ERROR;
              } else {
                if (!memcmp (D->word, "HTTP/1.0", 8)) {
                  D->http_ver = HTTP_V10;
                } else if (!memcmp (D->word, "HTTP/1.1", 8)) {
                  D->http_ver = HTTP_V11;
                } else {
                  c->parse_state = htqp_skiptoeoln;
                  D->query_flags |= QF_ERROR;
                }
              }
            } else {
              D->http_ver = HTTP_V09;
            }
          } else {
            assert (D->query_flags & (QF_HOST | QF_CONNECTION));
            if (D->wlen) {
              if (D->query_flags & QF_HOST) {
                D->host_offset = D->header_size;
                D->host_size = D->wlen;
              } else if (D->wlen == 10 && !strncasecmp (D->word, "keep-alive", 10)) {
                D->query_flags |= QF_KEEPALIVE;
              }
            }
            D->query_flags &= ~(QF_HOST | QF_CONNECTION);
            c->parse_state = htqp_skipspctoeoln;
          }
          D->header_size += D->wlen;
          break;

        case htqp_skipspc:
        case htqp_skipspctoeoln:
          //fprintf (stderr, "htqp_skipspc[toeoln]: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);
          while (D->header_size < MAX_HTTP_HEADER_SIZE && ptr < ptr_e && (*ptr == ' ' || (*ptr == '\t' && D->query_words >= 8))) {
            D->header_size++;
            ptr++;
          }
          if (D->header_size >= MAX_HTTP_HEADER_SIZE) {
            c->parse_state = htqp_fatal;
            break;
          }
          if (ptr == ptr_e) {
            break;
          }
          if (c->parse_state == htqp_skipspctoeoln) {
            c->parse_state = htqp_eoln;
            break;
          }
          if (D->query_words < 3) {
            D->wlen = 0;
            c->parse_state = htqp_readtospace;
          } else {
            assert (D->query_words >= 4);
            if (D->query_flags & QF_DATASIZE) {
              if (D->data_size != -1) {
                c->parse_state = htqp_skiptoeoln;
                D->query_flags |= QF_ERROR;
              } else {
                c->parse_state = htqp_readint;
                D->data_size = 0;
              }
            } else if (D->query_flags & (QF_HOST | QF_CONNECTION)) {
              D->wlen = 0;
              c->parse_state = htqp_readtospace;
            } else {
              c->parse_state = htqp_skiptoeoln;
            }
          }
          break;

        case htqp_readtocolon:
          //fprintf (stderr, "htqp_readtocolon: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);
          while (ptr < ptr_e && *ptr != ':' && *ptr > ' ') {
            if (D->wlen < 15) {
              D->word[D->wlen] = *ptr;
            }
            D->wlen++;
            ptr++;
          }
          if (D->wlen > 4096) {
            c->parse_state = htqp_fatal;
            break;
          }
          if (ptr == ptr_e) {
            break;
          }

          if (*ptr != ':') {
            D->header_size += D->wlen;
            c->parse_state = htqp_skiptoeoln;
            D->query_flags |= QF_ERROR;
            break;
          }

          ptr++;

          if (D->wlen == 4 && !strncasecmp (D->word, "host", 4)) {
            D->query_flags |= QF_HOST;
          } else if (D->wlen == 10 && !strncasecmp (D->word, "connection", 10)) {
            D->query_flags |= QF_CONNECTION;
          } else if (D->wlen == 14 && !strncasecmp (D->word, "content-length", 14)) {
            D->query_flags |= QF_DATASIZE;
          } else {
            D->query_flags &= ~(QF_HOST | QF_DATASIZE | QF_CONNECTION);
          }

          D->header_size += D->wlen + 1;
          c->parse_state = htqp_skipspc;
          break;

        case htqp_readint:	
          //fprintf (stderr, "htqp_readint: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);

          tt = D->data_size;
          while (ptr < ptr_e && *ptr >= '0' && *ptr <= '9') {
            if (tt >= 0x7fffffffL / 10) {
              D->query_flags |= QF_ERROR;
              c->parse_state = htqp_skiptoeoln;
              break;
            }
            tt = tt*10 + (*ptr - '0');
            ptr++;
            D->header_size++;
            D->query_flags &= ~QF_DATASIZE;
          }

          D->data_size = tt;
          if (ptr == ptr_e) {
            break;
          }

          if (D->query_flags & QF_DATASIZE) {
            D->query_flags |= QF_ERROR;
            c->parse_state = htqp_skiptoeoln;
          } else {
            c->parse_state = htqp_skipspctoeoln;
          }
          break;

        case htqp_skiptoeoln:
          //fprintf (stderr, "htqp_skiptoeoln: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);

          while (D->header_size < MAX_HTTP_HEADER_SIZE && ptr < ptr_e && (*ptr != '\r' && *ptr != '\n')) {
            D->header_size++;
            ptr++;
          }
          if (D->header_size >= MAX_HTTP_HEADER_SIZE) {
            c->parse_state = htqp_fatal;
            break;
          }
          if (ptr == ptr_e) {
            break;
          }

          c->parse_state = htqp_eoln;

        case htqp_eoln:

          if (ptr == ptr_e) {
            break;
          }
          if (*ptr == '\r') {
            ptr++;
            D->header_size++;
          }
          c->parse_state = htqp_wantlf;

        case htqp_wantlf:
          //fprintf (stderr, "htqp_wantlf: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);

          if (ptr == ptr_e) {
            break;
          }
          if (++D->query_words < 8) {
            D->query_words = 8;
            if (D->query_flags & QF_ERROR) {
              c->parse_state = htqp_fatal;
              break;
            }
          }

          if (D->http_ver <= HTTP_V09) {
            c->parse_state = htqp_wantlastlf;
            break;
          }

          if (*ptr != '\n') {
            D->query_flags |= QF_ERROR;
            c->parse_state = htqp_skiptoeoln;
            break;
          }

          ptr++;
          D->header_size++;

          c->parse_state = htqp_linestart;

        case htqp_linestart:
          //fprintf (stderr, "htqp_linestart: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);

          if (ptr == ptr_e) {
            break;
          }

          if (!D->first_line_size) {
            D->first_line_size = D->header_size;
          }

          if (*ptr == '\r') {
            ptr++;
            D->header_size++;
            c->parse_state = htqp_wantlastlf;
            break;
          }
          if (*ptr == '\n') {
            c->parse_state = htqp_wantlastlf;
            break;
          }

          if (D->query_flags & QF_ERROR) {
            c->parse_state = htqp_skiptoeoln;
          } else {
            D->wlen = 0;
            c->parse_state = htqp_readtocolon;
          }
          break;

        case htqp_wantlastlf:
          //fprintf (stderr, "htqp_wantlastlf: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);

          if (ptr == ptr_e) {
            break;
          }
          if (*ptr != '\n') {
            c->parse_state = htqp_fatal;
            break;
          }
          ptr++;
          D->header_size++;

          if (!D->first_line_size) {
            D->first_line_size = D->header_size;
          }

          c->parse_state = htqp_done;

        case htqp_done:
          //fprintf (stderr, "htqp_done: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);
          break;

        case htqp_fatal:
          //fprintf (stderr, "htqp_fatal: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->query_flags, D->query_words);
          D->query_flags |= QF_ERROR;
          c->parse_state = htqp_done;
          break;

        default:
          assert (0);
      }
    }

    len = ptr - ptr_s;
    nbit_advance (&c->Q, len);

    if (c->parse_state == htqp_done) {
      if (D->header_size >= MAX_HTTP_HEADER_SIZE) {
        D->query_flags |= QF_ERROR;
      }
      if (!(D->query_flags & QF_ERROR)) {
        c->status = conn_running;
        if (!HTS_FUNC(c)->execute) {
          HTS_FUNC(c)->execute = hts_default_execute;
        }
        int res;
        if (D->query_type == htqt_post && D->data_size < 0) {
          assert (advance_skip_read_ptr (&c->In, D->header_size) == D->header_size);
          res = -411;
        } else if (D->query_type != htqt_post && D->data_size > 0) {
          res = -413;
        } else {
          res = HTS_FUNC(c)->execute (c, D->query_type);
        }
        http_queries++;
        http_queries_size += D->header_size + D->data_size;
        if (res > 0) {
          c->status = conn_reading_query;
          return res;	// need more bytes
        } else if (res < 0) {
          if (res == SKIP_ALL_BYTES) {
            assert (advance_skip_read_ptr (&c->In, D->header_size) == D->header_size);
            if (D->data_size > 0) {
              len = advance_skip_read_ptr (&c->In, D->data_size);
              if (len < D->data_size) {
                c->parse_state = htqp_start;
                if (c->status == conn_running) {
                  c->status = conn_expect_query;
                }
                return len - D->data_size;
              }
            }
          } else {
            if (res == -413) {
              D->query_flags &= ~QF_KEEPALIVE;
            }
            write_http_error (c, -res);
            D->query_flags &= ~QF_ERROR;
          }
        }
        if (c->status == conn_running) {
          c->status = conn_expect_query;
        }

        //assert ((c->pending_queries && (c->status == conn_wait_net || c->status == conn_wait_aio)) || (!c->pending_queries && c->status == conn_expect_query));
        assert (c->status == conn_wait_net || (c->pending_queries && c->status == conn_wait_aio) || (!c->pending_queries && c->status == conn_expect_query));

      } else {
        //fprintf (stderr, "[parse error]\n");
        assert (advance_skip_read_ptr (&c->In, D->header_size) == D->header_size);
        c->status = conn_expect_query;
        http_bad_headers++;
      }
      if (D->query_flags & QF_ERROR) {
        assert (c->status == conn_expect_query);
        D->query_flags &= ~QF_KEEPALIVE;
        write_http_error (c, 400);
      }
      if (c->status == conn_expect_query && !(D->query_flags & QF_KEEPALIVE)) {
        c->status = conn_write_close;
        c->parse_state = -1;
        return 0;
      }
      if (c->status != conn_wait_aio) {
        c->parse_state = htqp_start;
      }
      nbit_set (&c->Q, &c->In);
    }
  }
  if (c->status == conn_reading_query || c->status == conn_wait_aio) {
    return NEED_MORE_BYTES;
  }
  return 0;
}