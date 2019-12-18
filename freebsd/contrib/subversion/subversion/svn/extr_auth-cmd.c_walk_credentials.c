#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_x509_certinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct walk_credentials_baton_t {scalar_t__ delete; int /*<<< orphan*/  show_passwords; scalar_t__ list; int /*<<< orphan*/  matches; TYPE_1__* patterns; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_2__ {scalar_t__ nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  list_credential (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_credential (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,char const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/ * svn_sort__hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sort_compare_items_lexically ; 

__attribute__((used)) static svn_error_t *
walk_credentials(svn_boolean_t *delete_cred,
                 void *baton,
                 const char *cred_kind,
                 const char *realmstring,
                 apr_hash_t *cred_hash,
                 apr_pool_t *scratch_pool)
{
  struct walk_credentials_baton_t *b = baton;
  apr_array_header_t *sorted_cred_items;
  svn_x509_certinfo_t *certinfo = NULL;

  *delete_cred = FALSE;

  sorted_cred_items = svn_sort__hash(cred_hash,
                                     svn_sort_compare_items_lexically,
                                     scratch_pool);
  if (b->patterns->nelts > 0)
    {
      svn_boolean_t match;

      SVN_ERR(match_credential(&match, &certinfo, cred_kind, realmstring,
                               b->patterns, sorted_cred_items,
                               scratch_pool, scratch_pool));
      if (!match)
        return SVN_NO_ERROR;
    }

  b->matches++;

  if (b->list)
    SVN_ERR(list_credential(cred_kind, realmstring, sorted_cred_items,
                            b->show_passwords, certinfo, scratch_pool));
  if (b->delete)
    {
      *delete_cred = TRUE;
      SVN_ERR(svn_cmdline_printf(scratch_pool,
                                 _("Deleting %s credential for realm '%s'\n"),
                                 cred_kind, realmstring));
    }

  return SVN_NO_ERROR;
}