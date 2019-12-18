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
struct tl_saved_query {scalar_t__ extra; } ;
struct tl_act_extra {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void tl_query_act_free_extra (struct tl_saved_query *q) {
  ((struct tl_act_extra *)(q->extra))->free (q->extra);
}