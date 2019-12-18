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
struct htc_data {int response_code; int data_size; int wlen; char* word; int response_words; int response_flags; scalar_t__ location_offset; scalar_t__ header_size; int location_size; scalar_t__ first_line_size; int /*<<< orphan*/  http_ver; } ;
struct connection {scalar_t__ status; int parse_state; int /*<<< orphan*/  In; int /*<<< orphan*/  Q; } ;
struct TYPE_2__ {int (* execute ) (struct connection*,int) ;} ;

/* Variables and functions */
 struct htc_data* HTC_DATA (struct connection*) ; 
 TYPE_1__* HTC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  HTTP_V10 ; 
 int /*<<< orphan*/  HTTP_V11 ; 
 scalar_t__ MAX_HTTP_HEADER_SIZE ; 
 int NEED_MORE_BYTES ; 
 int RF_CONNECTION ; 
 int RF_DATASIZE ; 
 int RF_ERROR ; 
 int RF_KEEPALIVE ; 
 int RF_LOCATION ; 
 int SKIP_ALL_BYTES ; 
 int advance_skip_read_ptr (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_reading_answer ; 
 scalar_t__ conn_running ; 
 scalar_t__ conn_wait_aio ; 
 scalar_t__ conn_wait_answer ; 
 scalar_t__ conn_write_close ; 
 int htc_default_execute (struct connection*,int) ; 
#define  htrp_done 140 
#define  htrp_eoln 139 
#define  htrp_fatal 138 
#define  htrp_linestart 137 
#define  htrp_readint 136 
#define  htrp_readtocolon 135 
#define  htrp_readtospace 134 
#define  htrp_skipspc 133 
#define  htrp_skipspctoeoln 132 
#define  htrp_skiptoeoln 131 
#define  htrp_start 130 
#define  htrp_wantlastlf 129 
#define  htrp_wantlf 128 
 void* htrt_error ; 
 int htrt_none ; 
 int /*<<< orphan*/  http_bad_response_headers ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct htc_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nbit_advance (int /*<<< orphan*/ *,int) ; 
 char* nbit_get_ptr (int /*<<< orphan*/ *) ; 
 int nbit_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outbound_http_queries ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int strtoul (char*,char**,int) ; 
 int stub1 (struct connection*,int) ; 

int htc_parse_execute (struct connection *c) {
  struct htc_data *D = HTC_DATA(c);
  char *ptr, *ptr_s, *ptr_e;
  int len;
  long long tt;

  while (c->status == conn_wait_answer || c->status == conn_reading_answer) {
    len = nbit_ready_bytes (&c->Q);
    ptr = ptr_s = nbit_get_ptr (&c->Q);
    ptr_e = ptr + len;
    if (len <= 0) {
      break;
    }

    while (ptr < ptr_e && c->parse_state != htrp_done) {

      switch (c->parse_state) {
      case htrp_start:
          //fprintf (stderr, "htrp_start: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);
	memset (D, 0, sizeof (*D));
	D->response_code = htrt_none;
	D->data_size = -1;
	c->parse_state = htrp_readtospace;

      case htrp_readtospace:
          //fprintf (stderr, "htrp_readtospace: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);
	while (ptr < ptr_e && ((unsigned) *ptr > ' ')) {
	  if (D->wlen < 15) {
	    D->word[D->wlen] = *ptr;
	  }
	  D->wlen++;
	  ptr++;
	}
	if (D->wlen > 4096) {
	  c->parse_state = htrp_fatal;
	  break;
	}
	if (ptr == ptr_e) {
	  break;
	}
	c->parse_state = htrp_skipspc;
	D->response_words++;
	if (D->response_words == 1) {
	  if (!memcmp (D->word, "HTTP/1.0", 8)) {
	    D->http_ver = HTTP_V10;
	    D->response_flags &= ~RF_KEEPALIVE;
	  } else if (!memcmp (D->word, "HTTP/1.1", 8)) {
	    D->http_ver = HTTP_V11;
	    D->response_flags |= RF_KEEPALIVE;
	  } else {
	    c->parse_state = htrp_skiptoeoln;
	    D->response_flags |= RF_ERROR;
	  }
	} else if (D->response_words == 2) {
	  D->response_code = htrt_error;
	  if (D->wlen == 3) {
	    D->word[3] = 0;
	    char *tmp;
	    D->response_code = strtoul (D->word, &tmp, 10);
	    if (tmp != D->word + 3 || D->response_code < 100 || D->response_code > 599) {
	      D->response_code = htrt_error;
	    }
	  }
	  if (D->response_code == htrt_error) {
	    D->response_flags |= RF_ERROR;
	  }
	  c->parse_state = htrp_skiptoeoln;
	} else {
	  assert (D->response_flags & (RF_LOCATION | RF_CONNECTION));
	  if (D->wlen) {
	    if (D->response_flags & RF_LOCATION) {
	      D->location_offset = D->header_size;
	      D->location_size = D->wlen;
	    } else {
	      if (D->wlen == 10 && !strncasecmp (D->word, "keep-alive", 10)) {
		D->response_flags |= RF_KEEPALIVE;
	      } else if (D->wlen == 5 && !strncasecmp (D->word, "close", 5)) {
		D->response_flags &= ~RF_KEEPALIVE;
	      }
	    }
	  }
	  D->response_flags &= ~(RF_LOCATION | RF_CONNECTION);
	  c->parse_state = htrp_skipspctoeoln;
	}
	D->header_size += D->wlen;
	break;

      case htrp_skipspc:
      case htrp_skipspctoeoln:
	//fprintf (stderr, "htrp_skipspc[toeoln]: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);
	while (D->header_size < MAX_HTTP_HEADER_SIZE && ptr < ptr_e && (*ptr == ' ' || (*ptr == '\t' && D->response_words >= 8))) {
	  D->header_size++;
	  ptr++;
	}
	if (D->header_size >= MAX_HTTP_HEADER_SIZE) {
	  c->parse_state = htrp_fatal;
	  break;
	}
	if (ptr == ptr_e) {
	  break;
	}
	if (c->parse_state == htrp_skipspctoeoln) {
	  c->parse_state = htrp_eoln;
	  break;
	}
	if (D->response_words < 2) {
	  D->wlen = 0;
	  c->parse_state = htrp_readtospace;
	} else {
	  assert (D->response_words >= 3);
	  if (D->response_flags & RF_DATASIZE) {
	    if (D->data_size != -1) {
	      c->parse_state = htrp_skiptoeoln;
	      D->response_flags |= RF_ERROR;
	    } else {
	      c->parse_state = htrp_readint;
	      D->data_size = 0;
	    }
	  } else if (D->response_flags & (RF_LOCATION | RF_CONNECTION)) {
	    D->wlen = 0;
	    c->parse_state = htrp_readtospace;
	  } else {
	    c->parse_state = htrp_skiptoeoln;
	  }
	}
	break;
      case htrp_readtocolon:
	//fprintf (stderr, "htrp_readtocolon: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);
	while (ptr < ptr_e && *ptr != ':' && *ptr > ' ') {
	  if (D->wlen < 15) {
	    D->word[D->wlen] = *ptr;
	  }
	  D->wlen++;
	  ptr++;
	}
	if (D->wlen > 4096) {
	  c->parse_state = htrp_fatal;
	  break;
	}
	if (ptr == ptr_e) {
	  break;
	}

	if (*ptr != ':') {
	  D->header_size += D->wlen;
	  c->parse_state = htrp_skiptoeoln;
	  D->response_flags |= RF_ERROR;
	  break;
	}

	ptr++;

	if (D->wlen == 8 && !strncasecmp (D->word, "location", 8)) {
	  D->response_flags |= RF_LOCATION;
	} else if (D->wlen == 10 && !strncasecmp (D->word, "connection", 10)) {
	  D->response_flags |= RF_CONNECTION;
	} else if (D->wlen == 14 && !strncasecmp (D->word, "content-length", 14)) {
	  D->response_flags |= RF_DATASIZE;
	} else {
	  D->response_flags &= ~(RF_LOCATION | RF_DATASIZE | RF_CONNECTION);
	}

	D->header_size += D->wlen + 1;
	c->parse_state = htrp_skipspc;
	break;

      case htrp_readint:	
	//fprintf (stderr, "htrp_readint: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);

	tt = D->data_size;
	while (ptr < ptr_e && *ptr >= '0' && *ptr <= '9') {
	  if (tt >= 0x7fffffffL / 10) {
	    D->response_flags |= RF_ERROR;
	    c->parse_state = htrp_skiptoeoln;
	    break;
	  }
	  tt = tt*10 + (*ptr - '0');
	  ptr++;
	  D->header_size++;
	  D->response_flags &= ~RF_DATASIZE;
	}

	D->data_size = tt;
	if (ptr == ptr_e) {
	  break;
	}

	if (D->response_flags & RF_DATASIZE) {
	  D->response_flags |= RF_ERROR;
	  c->parse_state = htrp_skiptoeoln;
	} else {
	  c->parse_state = htrp_skipspctoeoln;
	}
	break;

      case htrp_skiptoeoln:
	//fprintf (stderr, "htrp_skiptoeoln: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);

	while (D->header_size < MAX_HTTP_HEADER_SIZE && ptr < ptr_e && (*ptr != '\r' && *ptr != '\n')) {
	  D->header_size++;
	  ptr++;
	}
	if (D->header_size >= MAX_HTTP_HEADER_SIZE) {
	  c->parse_state = htrp_fatal;
	  break;
	}
	if (ptr == ptr_e) {
	  break;
	}

	c->parse_state = htrp_eoln;

      case htrp_eoln:

	if (ptr == ptr_e) {
	  break;
	}
	if (*ptr == '\r') {
	  ptr++;
	  D->header_size++;
	}
	c->parse_state = htrp_wantlf;

      case htrp_wantlf:
	//fprintf (stderr, "htrp_wantlf: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);

	if (ptr == ptr_e) {
	  break;
	}
	if (++D->response_words < 8) {
	  D->response_words = 8;
	  if (D->response_flags & RF_ERROR) {
	    c->parse_state = htrp_fatal;
	    break;
	  }
	}

	if (*ptr != '\n') {
	  D->response_flags |= RF_ERROR;
	  c->parse_state = htrp_skiptoeoln;
	  break;
	}

	ptr++;
	D->header_size++;

	c->parse_state = htrp_linestart;

      case htrp_linestart:
	//fprintf (stderr, "htrp_linestart: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);

	if (ptr == ptr_e) {
	  break;
	}

	if (!D->first_line_size) {
	  D->first_line_size = D->header_size;
	}

	if (*ptr == '\r') {
	  ptr++;
	  D->header_size++;
	  c->parse_state = htrp_wantlastlf;
	  break;
	}
	if (*ptr == '\n') {
	  c->parse_state = htrp_wantlastlf;
	  break;
	}

	if (D->response_flags & RF_ERROR) {
	  c->parse_state = htrp_skiptoeoln;
	} else {
	  D->wlen = 0;
	  c->parse_state = htrp_readtocolon;
	}
	break;

      case htrp_wantlastlf:
	//fprintf (stderr, "htrp_wantlastlf: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);

	if (ptr == ptr_e) {
	  break;
	}
	if (*ptr != '\n') {
	  c->parse_state = htrp_fatal;
	  break;
	}
	ptr++;
	D->header_size++;

	if (!D->first_line_size) {
	  D->first_line_size = D->header_size;
	}

	c->parse_state = htrp_done;

      case htrp_done:
	//fprintf (stderr, "htrp_done: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);
	break;

      case htrp_fatal:
	//fprintf (stderr, "htrp_fatal: ptr=%p (%.8s), hsize=%d, qf=%d, words=%d\n", ptr, ptr, D->header_size, D->response_flags, D->response_words);
	D->response_flags |= RF_ERROR;
	c->parse_state = htrp_done;
	break;

      default:
	assert (0);
      }
    }

    len = ptr - ptr_s;
    nbit_advance (&c->Q, len);

    if (c->parse_state == htrp_done) {
      if (D->header_size >= MAX_HTTP_HEADER_SIZE) {
        D->response_flags |= RF_ERROR;
      }

      if (D->response_flags & RF_ERROR) {
	D->response_code = -1;
        http_bad_response_headers++;
      }

      c->status = conn_running;
      if (!HTC_FUNC(c)->execute) {
	HTC_FUNC(c)->execute = htc_default_execute;
      }
      int res = HTC_FUNC(c)->execute (c, D->response_code);
      outbound_http_queries++;
      if (res > 0) {
	c->status = conn_reading_answer;
	return res;	// need more bytes
      } else if (res < 0) {
	if (res == SKIP_ALL_BYTES) {
	  assert (advance_skip_read_ptr (&c->In, D->header_size) == D->header_size);
	  if (D->data_size > 0) {
	    len = advance_skip_read_ptr (&c->In, D->data_size);
	    if (len < D->data_size) {
	      c->parse_state = htrp_start;
	      if (c->status == conn_running) {
		c->status = conn_wait_answer;
	      }
	      return len - D->data_size;
	    }
	  }
	} else {
	  D->response_flags &= ~RF_ERROR;
	}
      }
      if (c->status == conn_running) {
	c->status = conn_wait_answer;
      }

      if (D->response_flags & RF_ERROR) {
        assert (c->status == conn_wait_answer);
        D->response_flags &= ~RF_KEEPALIVE;
      }
      if (c->status == conn_wait_answer && !(D->response_flags & RF_KEEPALIVE)) {
        c->status = conn_write_close;
        c->parse_state = -1;
        return 0;
      }
      if (c->status != conn_wait_aio) {
        c->parse_state = htrp_start;
      }
      nbit_set (&c->Q, &c->In);
    }
  }
  if (c->status == conn_reading_answer || c->status == conn_wait_aio) {
    return NEED_MORE_BYTES;
  }
  return 0;
}