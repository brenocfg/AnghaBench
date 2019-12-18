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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ compute_crc32 (int*,int) ; 

void prepare_rpc_query_raw (int packet_id, int *q, int qn) {
  assert (sizeof (int) == 4);
  q[0] = qn;
  assert ((qn & 3) == 0);
  qn >>= 2;
  assert (qn >= 5);

  q[1] = packet_id;
  q[qn - 1] = (int)compute_crc32 (q, q[0] - 4);
}