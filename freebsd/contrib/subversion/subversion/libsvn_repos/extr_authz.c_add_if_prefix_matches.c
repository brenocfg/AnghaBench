#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
struct TYPE_10__ {TYPE_4__* node; } ;
typedef  TYPE_3__ sorted_pattern_t ;
struct TYPE_8__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__ segment; } ;
typedef  TYPE_4__ node_t ;
typedef  int /*<<< orphan*/  lookup_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_next_node (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
add_if_prefix_matches(lookup_state_t *state,
                      const sorted_pattern_t *prefix,
                      const svn_stringbuf_t *segment)
{
  node_t *node = prefix->node;
  if (   node->segment.len <= segment->len
      && !memcmp(node->segment.data, segment->data, node->segment.len))
    add_next_node(state, node);
}