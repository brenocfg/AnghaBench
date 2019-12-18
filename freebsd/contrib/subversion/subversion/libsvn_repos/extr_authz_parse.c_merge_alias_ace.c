#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  aces; TYPE_4__* cb; } ;
typedef  TYPE_1__ merge_alias_baton_t ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  access; int /*<<< orphan*/  inverted; } ;
typedef  TYPE_2__ authz_ace_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  parser_pool; int /*<<< orphan*/  parsed_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_INVALID_CONFIG ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrcat (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 char* intern_string (TYPE_4__*,char const*,int) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 void* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,TYPE_2__*) ; 

__attribute__((used)) static svn_error_t *
merge_alias_ace(void *baton,
                const void *key,
                apr_ssize_t klen,
                void *value,
                apr_pool_t *scratch_pool)
{
  merge_alias_baton_t *const mab = baton;
  authz_ace_t *aliased_ace = value;
  const char *alias = aliased_ace->name;
  const char *unaliased_key;
  const char *user;
  authz_ace_t *ace;

  user = svn_hash_gets(mab->cb->parsed_aliases, alias);
  if (!user)
    return svn_error_createf(
        SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
        _("Alias '%s' was never defined"),
        alias);

  /* N.B.: The user name is always internalized,
     but the inverted key may not be. */
  if (!aliased_ace->inverted)
    unaliased_key = user;
  else
    {
      unaliased_key = apr_pstrcat(mab->cb->parser_pool,
                                  "~", user, SVN_VA_NULL);
      unaliased_key = intern_string(mab->cb, unaliased_key, -1);
    }

  ace = svn_hash_gets(mab->aces, unaliased_key);
  if (!ace)
    {
      aliased_ace->name = user;
      svn_hash_sets(mab->aces, unaliased_key, aliased_ace);
    }
  else
    {
      SVN_ERR_ASSERT(!ace->inverted == !aliased_ace->inverted);
      ace->access |= aliased_ace->access;
    }

  return SVN_NO_ERROR;
}