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
typedef  int /*<<< orphan*/  query_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * new_query_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qn_true ; 

__attribute__((used)) static query_node_t *make_universal_node (void) {
  return new_query_node (qn_true);
  /*  --- the following optimization is incorrect in general ---
      if (!Q_universal) {
      Q_universal = new_query_node (qn_true);
      }
      return Q_universal;
   */
}