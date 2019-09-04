#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned short ilen; scalar_t__ start; } ;
typedef  TYPE_1__ dns_read_iterator_t ;

/* Variables and functions */
 scalar_t__ dns_read_iterator_fetch_uchar (TYPE_1__*,unsigned char*) ; 
 scalar_t__ dns_read_iterator_fetch_uchars (TYPE_1__*,int,unsigned char*) ; 
 int /*<<< orphan*/  dns_read_iterator_init (TYPE_1__*,scalar_t__,unsigned short) ; 

__attribute__((used)) static int dns_read_iterator_fetch_name (dns_read_iterator_t *B, char *output, char *wptr, int avail_out) {
  for (;;) {
    unsigned char c;
    if (dns_read_iterator_fetch_uchar (B, &c) < 0) {
      return -1;
    }
    if (!c) {
      break;
    }
    if ((c & 0xc0) == 0xc0) {
      /* 4.1.4. Message compression */
      unsigned char d;
      c &= 63;
      if (dns_read_iterator_fetch_uchar (B, &d) < 0) {
        return -1;
      }
      unsigned short off = (c & 63) * 256 + d;
      if (off >= B->ilen) {
        return -1;
      }
      dns_read_iterator_t B2;
      dns_read_iterator_init (&B2, B->start + off, B->ilen - off);
      if (dns_read_iterator_fetch_name (&B2, output, wptr, avail_out) < 0) {
        return -1;
      }
      return 0;
    }
    if (c & 0xc0) {
      return -1;
    }
    int l = c;
    if (!l) {
      break;
    }
    if (output != wptr) {
      if (avail_out <= 0) {
        return -1;
      }
      avail_out--;
      *wptr++ = '.';
    }
    if (avail_out < l) {
      return -1;
    }
    if (dns_read_iterator_fetch_uchars (B, l, (unsigned char *) wptr) < 0) {
      return -1;
    }
    avail_out -= l;
    wptr += l;
  }
  if (avail_out <= 0) {
    return -1;
  }
  avail_out--;
  *wptr = 0;
  return wptr - output;
}