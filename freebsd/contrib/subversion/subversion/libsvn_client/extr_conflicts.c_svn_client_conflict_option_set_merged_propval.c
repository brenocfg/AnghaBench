#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_5__ {int /*<<< orphan*/  merged_propval; } ;
struct TYPE_6__ {TYPE_1__ prop; } ;
struct TYPE_7__ {int /*<<< orphan*/  pool; TYPE_2__ type_data; } ;
typedef  TYPE_3__ svn_client_conflict_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void
svn_client_conflict_option_set_merged_propval(
  svn_client_conflict_option_t *option,
  const svn_string_t *merged_propval)
{
  option->type_data.prop.merged_propval = svn_string_dup(merged_propval,
                                                         option->pool);
}