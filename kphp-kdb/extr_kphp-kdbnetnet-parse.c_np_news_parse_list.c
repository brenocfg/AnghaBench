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
struct nb_reader {int dummy; } ;
typedef  int /*<<< orphan*/  netbuffer_t ;
typedef  int /*<<< orphan*/  nb_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  advance_skip_read_ptr (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  nb_reader_parse_int (struct nb_reader*,int*,int*) ; 
 int /*<<< orphan*/  nb_reader_set (struct nb_reader*,int /*<<< orphan*/ *,int const) ; 
 int const nbit_read_in (int /*<<< orphan*/ *,int*,int const) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int np_news_parse_list (int *Res, const int max_size, const int arity, netbuffer_t *In, const int bytes) {
  if (!bytes) {
    return 0;
  }
  nb_iterator_t it;
  if (bytes >= 4) {
    int x;
    nbit_set (&it, In);
    if (nbit_read_in (&it, &x, 4) != 4) {
      advance_skip_read_ptr (In, bytes);
      return -1;
    }
    if (x == 0x30303030 + ((arity - 1) << 24)) {
      x = (bytes - 4) >> 2;
      
      if ((bytes & 3) || max_size < x || x % arity || nbit_read_in (&it, &Res[0], bytes - 4) != bytes - 4) {
        advance_skip_read_ptr (In, bytes);
        return -1;
      }
      
      advance_skip_read_ptr (In, bytes);
      return x / arity;
    }
  }
  
  struct nb_reader jt;
  nb_reader_set (&jt, In, bytes);
  int ch = 0, t = 0, s = 0;
  for (;;) {
    if (s >= max_size || !nb_reader_parse_int (&jt, &Res[s++], &ch)) {
      advance_skip_read_ptr (In, bytes);
      return -1;
    }
    if (ch < 0) {
      break;
    }
    if (++t == arity) {
      t = 0;
    }
    if (ch != (t ? '_' : ',')) {
      advance_skip_read_ptr (In, bytes);
      return -1;
    }
  }
  advance_skip_read_ptr (In, bytes);
  return (s % arity) ? -1 : s / arity;
}