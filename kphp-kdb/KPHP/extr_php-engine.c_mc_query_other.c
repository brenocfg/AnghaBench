#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct conn_query {scalar_t__ extra; } ;
struct TYPE_5__ {TYPE_1__* func; } ;
typedef  TYPE_2__ mc_ansgen_t ;
typedef  int /*<<< orphan*/  data_reader_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* other ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int pnet_query_check (struct conn_query*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

int mc_query_other (struct conn_query *q, data_reader_t *reader) {
  mc_ansgen_t *ansgen = (mc_ansgen_t *)q->extra;
  ansgen->func->other (ansgen, reader);

  int err = pnet_query_check (q);
  return err;
}