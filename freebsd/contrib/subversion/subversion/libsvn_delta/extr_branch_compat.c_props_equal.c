#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  props; } ;
typedef  TYPE_1__ svn_element__payload_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
props_equal(svn_element__payload_t *initial_payload,
            svn_element__payload_t *final_payload,
            apr_pool_t *scratch_pool)
{
  apr_array_header_t *prop_diffs;

  if (!initial_payload || !final_payload)
    return FALSE;

  svn_error_clear(svn_prop_diffs(&prop_diffs,
                                 initial_payload->props,
                                 final_payload->props,
                                 scratch_pool));
  return (prop_diffs->nelts == 0);
}