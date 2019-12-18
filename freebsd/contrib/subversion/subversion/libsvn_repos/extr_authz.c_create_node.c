#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sequence_number; } ;
struct TYPE_11__ {TYPE_2__ access; } ;
struct TYPE_9__ {char* data; scalar_t__ len; } ;
struct TYPE_12__ {TYPE_3__ rights; TYPE_1__ segment; } ;
typedef  TYPE_4__ node_t ;
struct TYPE_13__ {TYPE_1__ pattern; } ;
typedef  TYPE_5__ authz_rule_segment_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  NO_SEQUENCE_NUMBER ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static node_t *
create_node(authz_rule_segment_t *segment,
            apr_pool_t *result_pool)
{
  node_t *result = apr_pcalloc(result_pool, sizeof(*result));
  if (segment)
    result->segment = segment->pattern;
  else
    {
      result->segment.data = "";
      result->segment.len = 0;
    }
  result->rights.access.sequence_number = NO_SEQUENCE_NUMBER;
  return result;
}