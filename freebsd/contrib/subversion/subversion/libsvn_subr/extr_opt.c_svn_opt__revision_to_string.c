#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  date; int /*<<< orphan*/  number; } ;
struct TYPE_5__ {int kind; TYPE_1__ value; } ;
typedef  TYPE_2__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
#define  svn_opt_revision_base 135 
#define  svn_opt_revision_committed 134 
#define  svn_opt_revision_date 133 
#define  svn_opt_revision_head 132 
#define  svn_opt_revision_number 131 
#define  svn_opt_revision_previous 130 
#define  svn_opt_revision_unspecified 129 
#define  svn_opt_revision_working 128 
 char const* svn_time_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_opt__revision_to_string(const svn_opt_revision_t *revision,
                            apr_pool_t *result_pool)
{
  switch (revision->kind)
    {
      case svn_opt_revision_unspecified:
        return "unspecified";
      case svn_opt_revision_number:
        return apr_psprintf(result_pool, "%ld", revision->value.number);
      case svn_opt_revision_date:
        /* ### svn_time_to_human_cstring()? */
        return svn_time_to_cstring(revision->value.date, result_pool);
      case svn_opt_revision_committed:
        return "committed";
      case svn_opt_revision_previous:
        return "previous";
      case svn_opt_revision_base:
        return "base";
      case svn_opt_revision_working:
        return "working";
      case svn_opt_revision_head:
        return "head";
      default:
        return NULL;
    }
}