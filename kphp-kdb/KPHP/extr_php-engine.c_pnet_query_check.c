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
struct conn_query {scalar_t__ extra; } ;
struct TYPE_2__ {int state; } ;
typedef  TYPE_1__ net_ansgen_t ;
typedef  int ansgen_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  pnet_query_answer (struct conn_query*) ; 
 int /*<<< orphan*/  pnet_query_delete (struct conn_query*) ; 
#define  st_ansgen_done 130 
#define  st_ansgen_error 129 
#define  st_ansgen_wait 128 

int pnet_query_check (struct conn_query *q) {
  net_ansgen_t *net_ansgen = (net_ansgen_t *)q->extra;

  ansgen_state_t state = net_ansgen->state;
  switch (state) {
    case st_ansgen_done:
    case st_ansgen_error:
      pnet_query_answer (q);
      pnet_query_delete (q);
      break;

    case st_ansgen_wait:
      break;
  }

  return state == st_ansgen_error;
}