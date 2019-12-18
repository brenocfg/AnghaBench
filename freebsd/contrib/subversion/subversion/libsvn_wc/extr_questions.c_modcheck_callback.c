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
struct TYPE_4__ {int node_status; int const text_status; int const prop_status; int /*<<< orphan*/  actual_kind; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {void* found_not_delete; void* found_mod; int /*<<< orphan*/  ignore_unversioned; } ;
typedef  TYPE_2__ modcheck_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CEASE_INVOCATION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_node_unknown ; 
#define  svn_wc_status_added 139 
#define  svn_wc_status_deleted 138 
#define  svn_wc_status_external 137 
#define  svn_wc_status_ignored 136 
#define  svn_wc_status_incomplete 135 
#define  svn_wc_status_missing 134 
#define  svn_wc_status_modified 133 
#define  svn_wc_status_none 132 
#define  svn_wc_status_normal 131 
#define  svn_wc_status_obstructed 130 
#define  svn_wc_status_replaced 129 
#define  svn_wc_status_unversioned 128 

__attribute__((used)) static svn_error_t *
modcheck_callback(void *baton,
                  const char *local_abspath,
                  const svn_wc_status3_t *status,
                  apr_pool_t *scratch_pool)
{
  modcheck_baton_t *mb = baton;

  switch (status->node_status)
    {
      case svn_wc_status_normal:
      case svn_wc_status_ignored:
      case svn_wc_status_none:
      case svn_wc_status_external:
        break;

      case svn_wc_status_incomplete:
        if ((status->text_status != svn_wc_status_normal
             && status->text_status != svn_wc_status_none)
            || (status->prop_status != svn_wc_status_normal
                && status->prop_status != svn_wc_status_none))
          {
            mb->found_mod = TRUE;
            mb->found_not_delete = TRUE;
            /* Incomplete, but local modifications */
            return svn_error_create(SVN_ERR_CEASE_INVOCATION, NULL, NULL);
          }
        break;

      case svn_wc_status_deleted:
        mb->found_mod = TRUE;
        if (!mb->ignore_unversioned
            && status->actual_kind != svn_node_none
            && status->actual_kind != svn_node_unknown)
          {
            /* The delete is obstructed by something unversioned */
            mb->found_not_delete = TRUE;
            return svn_error_create(SVN_ERR_CEASE_INVOCATION, NULL, NULL);
          }
        break;

      case svn_wc_status_unversioned:
        if (mb->ignore_unversioned)
          break;
        /* else fall through */
      case svn_wc_status_missing:
      case svn_wc_status_obstructed:
        mb->found_mod = TRUE;
        mb->found_not_delete = TRUE;
        /* Exit from the status walker: We know what we want to know */
        return svn_error_create(SVN_ERR_CEASE_INVOCATION, NULL, NULL);

      default:
      case svn_wc_status_added:
      case svn_wc_status_replaced:
      case svn_wc_status_modified:
        mb->found_mod = TRUE;
        mb->found_not_delete = TRUE;
        /* Exit from the status walker: We know what we want to know */
        return svn_error_create(SVN_ERR_CEASE_INVOCATION, NULL, NULL);
    }

  return SVN_NO_ERROR;
}