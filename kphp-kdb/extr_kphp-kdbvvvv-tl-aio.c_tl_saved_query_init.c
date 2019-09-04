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
struct tl_saved_query {int /*<<< orphan*/  fail; int /*<<< orphan*/  attempt; int /*<<< orphan*/  pid; int /*<<< orphan*/  qid; int /*<<< orphan*/  out_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  attempt_num; int /*<<< orphan*/  out_qid; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TL_IN_PID ; 
 int /*<<< orphan*/  TL_IN_TYPE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 TYPE_1__ tl ; 
 int /*<<< orphan*/  tl_default_aio_fail ; 
 struct tl_saved_query* zmalloc0 (int) ; 

struct tl_saved_query *tl_saved_query_init (void) {
  struct tl_saved_query *q = zmalloc0 (sizeof (struct tl_saved_query));
  q->out_type = TL_IN_TYPE;
  q->qid = tl.out_qid;
  assert (TL_IN_PID);
  q->pid = *TL_IN_PID;
  q->attempt = tl.attempt_num;
  q->fail = tl_default_aio_fail;
  return q;
}