#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_1__ segment; } ;
typedef  TYPE_3__ node_t ;
typedef  int /*<<< orphan*/  lookup_state_t ;
struct TYPE_13__ {int nelts; } ;
typedef  TYPE_4__ apr_array_header_t ;
struct TYPE_14__ {TYPE_3__* node; } ;

/* Variables and functions */
 TYPE_8__ APR_ARRAY_IDX (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_node (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ apr_fnmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorted_pattern_t ; 

__attribute__((used)) static void
add_complex_matches(lookup_state_t *state,
                    const svn_stringbuf_t *segment,
                    apr_array_header_t *patterns)
{
  int i;
  for (i = 0; i < patterns->nelts; ++i)
    {
      node_t *node = APR_ARRAY_IDX(patterns, i, sorted_pattern_t).node;
      if (0 == apr_fnmatch(node->segment.data, segment->data, 0))
        add_next_node(state, node);
    }
}