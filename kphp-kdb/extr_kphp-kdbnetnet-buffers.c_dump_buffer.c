#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; char* end; char* start; char* rptr; char* wptr; int /*<<< orphan*/  pptr; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSY ; 
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int dump_buffer (netbuffer_t *X, int num, int offset) {
  char *ptr;
  int i, s, c;
  assert (X->state == NB_MAGIC_HEAD || X->state == NB_MAGIC_BUSYHEAD || X->state == NB_MAGIC_BUSY);
  fprintf (stderr, "Dumping buffer #%d in chain at offset %d, addr=%p, size=%ld, start=%p, read=%p, pptr=%p, write=%p, end=%p\n",
    num, offset, X, (long)(X->end - X->start), X->start, X->rptr, X->pptr, X->wptr, X->end);
  ptr = X->start;
  while (ptr < X->end) {
    s = X->end - ptr;
    if (s > 16) { 
      s = 16;
    }
    fprintf (stderr, "%08x", (int) (ptr - X->start + offset));
    for (i = 0; i < 16; i++) {
      c = ' ';
      if (ptr + i == X->rptr) {
        c = '[';
      }
      if (ptr + i == X->wptr) {
        c = (c == '[' ? '|' : ']');
      }
      if (i == 8) {
        fputc (' ', stderr);
      }
      if (i < s) {
        fprintf (stderr, "%c%02x", c, (unsigned char) ptr[i]);
      } else {
        fprintf (stderr, "%c  ", c);
      }
    }
    c = ' ';
    if (ptr + 16 == X->end) {
      if (ptr + 16 == X->rptr) {
        c = '[';
      }
      if (ptr + 16 == X->wptr) {
        c = (c == '[' ? '|' : ']');
      }
      
    }
    fprintf (stderr, "%c  ", c);
    for (i = 0; i < s; i++) {
      putc ((unsigned char) ptr[i] < ' ' ? '.' : ptr[i], stderr);
    }
    putc ('\n', stderr);
    ptr += 16;
  }
  return X->end - X->start;
}