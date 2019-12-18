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
struct TYPE_2__ {int /*<<< orphan*/  out_packet_num; } ;

/* Variables and functions */
 TYPE_1__* RPCS_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TL_OUT_CONN ; 
 int TL_OUT_POS ; 
 int* TL_OUT_SIZE ; 

__attribute__((used)) static inline void __tl_conn_store_prefix (void) {
  int *p = TL_OUT_SIZE;
  p[0] = TL_OUT_POS + 24;
  p[1] = RPCS_DATA(TL_OUT_CONN)->out_packet_num ++;
}