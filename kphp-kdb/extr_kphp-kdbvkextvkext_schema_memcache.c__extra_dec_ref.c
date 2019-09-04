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
struct rpc_query {scalar_t__ extra_free; scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_REF (scalar_t__) ; 
 int /*<<< orphan*/  total_tl_working ; 

void _extra_dec_ref (struct rpc_query *q) {
  if (q->extra) {
    total_tl_working --;
  }
  DEC_REF (q->extra);
  q->extra = 0;
  q->extra_free = 0;
}