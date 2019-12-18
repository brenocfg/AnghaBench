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
struct connection {double last_query_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void accumulate_query_timeout (struct connection *c, double query_timeout) {
  if (c->last_query_timeout < query_timeout) {
    c->last_query_timeout = query_timeout;
    assert (query_timeout < 32);
  }
}