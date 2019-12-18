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
struct binlog_wait_query {scalar_t__ wait_pos; long long num; } ;

/* Variables and functions */

long long binlog_wait_query_cmp (struct binlog_wait_query *a, struct binlog_wait_query *b) {
  if (a->wait_pos != b->wait_pos) {
    return a->wait_pos - b->wait_pos;
  }
  return a->num - b->num;
}