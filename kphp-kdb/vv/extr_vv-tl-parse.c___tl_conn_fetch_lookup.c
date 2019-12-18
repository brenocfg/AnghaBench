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
typedef  int /*<<< orphan*/  nb_iterator_t ;
struct TYPE_2__ {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 TYPE_1__* TL_IN_CONN ; 
 int /*<<< orphan*/  assert (int) ; 
 int nbit_read_in (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __tl_conn_fetch_lookup (void *buf, int len) {
  nb_iterator_t R;
  nbit_set (&R, &TL_IN_CONN->In);
  assert (nbit_read_in (&R, buf, len) == len);
}