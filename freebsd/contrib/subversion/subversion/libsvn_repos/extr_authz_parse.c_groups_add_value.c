#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  parser_pool; int /*<<< orphan*/  parsed_groups; scalar_t__ parsing_groups; int /*<<< orphan*/  in_groups; } ;
typedef  TYPE_2__ ctor_baton_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_INVALID_CONFIG ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_get (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 char* apr_pstrcat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intern_string (TYPE_2__* const,char const*,scalar_t__) ; 
 scalar_t__ strchr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cstring_split (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static svn_error_t *
groups_add_value(void *baton, svn_stringbuf_t *section,
                 svn_stringbuf_t *option, svn_stringbuf_t *value)
{
  ctor_baton_t *const cb = baton;
  const char *group;
  apr_size_t group_len;

  SVN_ERR_ASSERT(cb->in_groups);

  if (strchr("@$&*~", *option->data))
    {
      if (cb->parsing_groups)
        return svn_error_createf(
            SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
            _("Global group name '%s' may not begin with '%c'"),
            option->data, *option->data);
      else
        return svn_error_createf(
            SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
            _("Group name '%s' may not begin with '%c'"),
            option->data, *option->data);
    }

  /* Decorate the name to make lookups consistent. */
  group = apr_pstrcat(cb->parser_pool, "@", option->data, SVN_VA_NULL);
  group_len = option->len + 1;
  if (apr_hash_get(cb->parsed_groups, group, group_len))
    {
      if (cb->parsing_groups)
        return svn_error_createf(SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
                                 _("Can't override definition"
                                   " of global group '%s'"),
                                 group);
      else
        return svn_error_createf(SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
                                 _("Can't override definition"
                                   " of group '%s'"),
                                 group);
    }

  /* We store the whole group definition, so that we can use the
     temporary groups in the baton hash later to fully expand group
     memberships.
     At this point, we can finally internalize the group name. */
  apr_hash_set(cb->parsed_groups,
               intern_string(cb, group, group_len), group_len,
               svn_cstring_split(value->data, ",", TRUE, cb->parser_pool));

  return SVN_NO_ERROR;
}