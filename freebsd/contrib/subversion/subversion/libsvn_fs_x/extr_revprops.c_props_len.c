#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  revprops; } ;
typedef  TYPE_1__ packed_revprops_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 TYPE_3__ APR_ARRAY_IDX (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_string_t ; 

__attribute__((used)) static apr_size_t
props_len(packed_revprops_t *revprops,
          int i)
{
  return APR_ARRAY_IDX(revprops->revprops, i, svn_string_t).len;
}