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
struct friends_gather_extra {int query_type; scalar_t__ list_id; } ;

/* Variables and functions */

int friends_use_preget_query (void *extra) {
  return (((struct friends_gather_extra *)extra)->query_type == 1) && (((struct friends_gather_extra *)extra)->list_id < 0);
}