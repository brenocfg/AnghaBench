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
struct connection {struct connection* next; struct connection* prev; } ;
struct conn_target {struct connection* last_conn; struct connection* first_conn; } ;

/* Variables and functions */

__attribute__((used)) static inline void rotate_target (struct conn_target *S, struct connection *c) {
  S->last_conn->next = S->first_conn;
  S->first_conn->prev = S->last_conn;
  S->first_conn = c->next;
  S->last_conn = c;
  S->first_conn->prev = S->last_conn->next = (struct connection *) S;
}