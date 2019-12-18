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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  scalar_t__ svn_client_conflict_option_id_t ;
struct TYPE_6__ {scalar_t__ choice; int /*<<< orphan*/  accept_arg; scalar_t__ code; } ;
typedef  TYPE_1__ resolver_option_t ;
struct TYPE_7__ {int is_recommended; int /*<<< orphan*/  accept_arg; int /*<<< orphan*/  long_desc; int /*<<< orphan*/  label; scalar_t__ code; scalar_t__ choice; } ;
typedef  TYPE_2__ client_option_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_client_conflict_get_recommended_option_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_option_get_description (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_option_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_option_get_label (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_option_unspecified ; 

__attribute__((used)) static svn_error_t *
find_option_by_builtin(client_option_t **out,
                       svn_client_conflict_t *conflict,
                       const resolver_option_t *options,
                       svn_client_conflict_option_t *builtin_option,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  const resolver_option_t *opt;
  svn_client_conflict_option_id_t id;
  svn_client_conflict_option_id_t recommended_id;

  id = svn_client_conflict_option_get_id(builtin_option);
  recommended_id = svn_client_conflict_get_recommended_option_id(conflict);

  for (opt = options; opt->code; opt++)
    {
      if (opt->choice == id)
        {
          client_option_t *client_opt;

          client_opt = apr_pcalloc(result_pool, sizeof(*client_opt));
          client_opt->choice = id;
          client_opt->code = opt->code;
          client_opt->label = svn_client_conflict_option_get_label(
              builtin_option,
              result_pool);
          client_opt->long_desc = svn_client_conflict_option_get_description(
                                    builtin_option,
                                    result_pool);
          client_opt->accept_arg = opt->accept_arg;
          client_opt->is_recommended =
            (recommended_id != svn_client_conflict_option_unspecified &&
             id == recommended_id);

          *out = client_opt;

          return SVN_NO_ERROR;
        }
    }

  *out = NULL;

  return SVN_NO_ERROR;
}