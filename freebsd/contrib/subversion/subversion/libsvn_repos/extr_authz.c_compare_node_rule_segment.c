#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* node; } ;
typedef  TYPE_4__ sorted_pattern_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_3__ pattern; } ;
typedef  TYPE_5__ authz_rule_segment_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_1__ segment; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_node_rule_segment(const void *void_lhs,
                          const void *void_rhs)
{
  const sorted_pattern_t *element = void_lhs;
  const authz_rule_segment_t *segment = void_rhs;

  return strcmp(element->node->segment.data, segment->pattern.data);
}