#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  parsed_aliases; int /*<<< orphan*/  parser_pool; } ;
typedef  TYPE_2__ ctor_baton_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_AUTHZ_INVALID_CONFIG ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_get (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,char const*,scalar_t__,char const*) ; 
 char* apr_pstrcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* intern_string (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  prepare_global_rights (TYPE_2__*,char const*) ; 
 scalar_t__ strchr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static svn_error_t *
add_alias_definition(ctor_baton_t *cb,
                     svn_stringbuf_t *option, svn_stringbuf_t *value)
{
  const char *alias;
  apr_size_t alias_len;
  const char *user;

  if (strchr("@$&*~", *option->data))
    return svn_error_createf(
        SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
        _("Alias name '%s' may not begin with '%c'"),
        option->data, *option->data);

  /* Decorate the name to make lookups consistent. */
  alias = apr_pstrcat(cb->parser_pool, "&", option->data, SVN_VA_NULL);
  alias_len = option->len + 1;
  if (apr_hash_get(cb->parsed_aliases, alias, alias_len))
    return svn_error_createf(
        SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
        _("Can't override definition of alias '%s'"),
        alias);

  user = intern_string(cb, value->data, value->len);
  apr_hash_set(cb->parsed_aliases, alias, alias_len, user);

  /* Prepare the global rights struct for this user. */
  prepare_global_rights(cb, user);
  return SVN_NO_ERROR;
}