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
typedef  int /*<<< orphan*/  query_t ;
typedef  int /*<<< orphan*/  condition_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITION_FALSE ; 
 int /*<<< orphan*/  CONDITION_TRUE ; 
 int /*<<< orphan*/  build_condition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

inline condition_t build_condition_from_query (query_t *Q, int opt_level) {
  return build_condition (Q, CONDITION_TRUE, CONDITION_FALSE, opt_level);
}