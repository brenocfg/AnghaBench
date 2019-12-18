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
struct connection {struct connection* next; } ;
struct conn_target {struct connection* first_conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_query ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_1__* MCC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 

void flush_conn (struct conn_target *S) {
  struct connection *c;
  if (!S) {
    return;
  }
  for (c = S->first_conn; c != (struct connection *)S; c = c->next) {
    MCC_FUNC (c)->flush_query (c);
  }
}