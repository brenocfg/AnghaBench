#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* base; scalar_t__ len; } ;
struct TYPE_9__ {TYPE_5__ buf; int /*<<< orphan*/  req; } ;
typedef  TYPE_2__ write_req_t ;
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_10__ {char* base; } ;
typedef  TYPE_3__ uv_buf_t ;
typedef  void* ssize_t ;
struct TYPE_8__ {char* prevbuf_ptr; int prevbuf_pos; int prevbuf_rem; } ;
struct TYPE_11__ {TYPE_1__ state; } ;
typedef  TYPE_4__ dnshandle ;

/* Variables and functions */
 int DNSREC_LEN ; 
 int /*<<< orphan*/  FATAL (char*) ; 
 int WRITE_BUF_LEN ; 
 int /*<<< orphan*/  addrsp (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  after_write ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_req(uv_stream_t* handle,
                        ssize_t nread,
                        const uv_buf_t* buf) {
  write_req_t* wr;
  dnshandle* dns = (dnshandle*)handle;
  char hdrbuf[DNSREC_LEN];
  int hdrbuf_remaining = DNSREC_LEN;
  int rec_remaining = 0;
  int readbuf_remaining;
  char* dnsreq;
  char* hdrstart;
  int usingprev = 0;

  wr = (write_req_t*) malloc(sizeof *wr);
  wr->buf.base = (char*)malloc(WRITE_BUF_LEN);
  wr->buf.len = 0;

  if (dns->state.prevbuf_ptr != NULL) {
    dnsreq = dns->state.prevbuf_ptr + dns->state.prevbuf_pos;
    readbuf_remaining = dns->state.prevbuf_rem;
    usingprev = 1;
  } else {
    dnsreq = buf->base;
    readbuf_remaining = nread;
  }
  hdrstart = dnsreq;

  while (dnsreq != NULL) {
    /* something to process */
    while (readbuf_remaining > 0) {
      /* something to process in current buffer */
      if (hdrbuf_remaining > 0) {
        /* process len and id */
        if (readbuf_remaining < hdrbuf_remaining) {
          /* too little to get request header. save for next buffer */
          memcpy(&hdrbuf[DNSREC_LEN - hdrbuf_remaining],
                 dnsreq,
                 readbuf_remaining);
          hdrbuf_remaining = DNSREC_LEN - readbuf_remaining;
          break;
        } else {
          /* save header */
          memcpy(&hdrbuf[DNSREC_LEN - hdrbuf_remaining],
                 dnsreq,
                 hdrbuf_remaining);
          dnsreq += hdrbuf_remaining;
          readbuf_remaining -= hdrbuf_remaining;
          hdrbuf_remaining = 0;

          /* get record length */
          rec_remaining = (unsigned) hdrbuf[0] * 256 + (unsigned) hdrbuf[1];
          rec_remaining -= (DNSREC_LEN - 2);
        }
      }

      if (rec_remaining <= readbuf_remaining) {
        /* prepare reply */
        addrsp(wr, hdrbuf);

        /* move to next record */
        dnsreq += rec_remaining;
        hdrstart = dnsreq;
        readbuf_remaining -= rec_remaining;
        rec_remaining = 0;
        hdrbuf_remaining = DNSREC_LEN;
      } else {
        /* otherwise this buffer is done. */
        rec_remaining -= readbuf_remaining;
        break;
      }
    }

    /* If we had to use bytes from prev buffer, start processing the current
     * one.
     */
    if (usingprev == 1) {
      /* free previous buffer */
      free(dns->state.prevbuf_ptr);
      dnsreq = buf->base;
      readbuf_remaining = nread;
      usingprev = 0;
    } else {
      dnsreq = NULL;
    }
  }

  /* send write buffer */
  if (wr->buf.len > 0) {
    if (uv_write((uv_write_t*) &wr->req, handle, &wr->buf, 1, after_write)) {
      FATAL("uv_write failed");
    }
  }

  if (readbuf_remaining > 0) {
    /* save start of record position, so we can continue on next read */
    dns->state.prevbuf_ptr = buf->base;
    dns->state.prevbuf_pos = hdrstart - buf->base;
    dns->state.prevbuf_rem = nread - dns->state.prevbuf_pos;
  } else {
    /* nothing left in this buffer */
    dns->state.prevbuf_ptr = NULL;
    dns->state.prevbuf_pos = 0;
    dns->state.prevbuf_rem = 0;
    free(buf->base);
  }
}