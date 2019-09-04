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
struct iovec {int iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  netbuffer_t ;
typedef  int /*<<< orphan*/  nb_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int nbit_advance (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nbit_get_ptr (int /*<<< orphan*/ *) ; 
 int nbit_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int prepare_iovec (struct iovec *iov, int *iovcnt, int maxcnt, netbuffer_t *H) {
  int t = 0, i;
  nb_iterator_t Iter;
  nbit_set (&Iter, H);

  for (i = 0; i < maxcnt; i++) {
    int s = nbit_ready_bytes (&Iter);
    if (s <= 0) {
      break;
    }
    iov[i].iov_len = s;
    iov[i].iov_base = nbit_get_ptr (&Iter);
    assert (nbit_advance (&Iter, s) == s);
    t += s;
  }

  *iovcnt = i;

  return t;
}