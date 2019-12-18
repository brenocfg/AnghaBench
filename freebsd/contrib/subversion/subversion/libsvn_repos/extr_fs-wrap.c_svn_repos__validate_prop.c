#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  scalar_t__ svn_prop_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BAD_PROPERTY_VALUE ; 
 int /*<<< orphan*/  SVN_ERR_BAD_PROPERTY_VALUE_EOL ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_ARGS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ svn_prop_is_svn_prop (char const*) ; 
 scalar_t__ svn_prop_needs_translation (char const*) ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/ * svn_time_from_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_utf__is_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_repos__validate_prop(const char *name,
                         const svn_string_t *value,
                         apr_pool_t *pool)
{
  svn_prop_kind_t kind = svn_property_kind2(name);

  /* Allow deleting any property, even a property we don't allow to set. */
  if (value == NULL)
    return SVN_NO_ERROR;

  /* Disallow setting non-regular properties. */
  if (kind != svn_prop_regular_kind)
    return svn_error_createf
      (SVN_ERR_REPOS_BAD_ARGS, NULL,
       _("Storage of non-regular property '%s' is disallowed through the "
         "repository interface, and could indicate a bug in your client"),
       name);

  /* Validate "svn:" properties. */
  if (svn_prop_is_svn_prop(name) && value != NULL)
    {
      /* Validate that translated props (e.g., svn:log) are UTF-8 with
       * LF line endings. */
      if (svn_prop_needs_translation(name))
        {
          if (!svn_utf__is_valid(value->data, value->len))
            {
              return svn_error_createf
                (SVN_ERR_BAD_PROPERTY_VALUE, NULL,
                 _("Cannot accept '%s' property because it is not encoded in "
                   "UTF-8"), name);
            }

          /* Disallow inconsistent line ending style, by simply looking for
           * carriage return characters ('\r'). */
          if (strchr(value->data, '\r') != NULL)
            {
              svn_error_t *err = svn_error_createf
                (SVN_ERR_BAD_PROPERTY_VALUE_EOL, NULL,
                 _("Cannot accept non-LF line endings in '%s' property"),
                   name);

              return svn_error_create(SVN_ERR_BAD_PROPERTY_VALUE, err,
                                      _("Invalid property value"));
            }
        }

      /* "svn:date" should be a valid date. */
      if (strcmp(name, SVN_PROP_REVISION_DATE) == 0)
        {
          apr_time_t temp;
          svn_error_t *err;

          err = svn_time_from_cstring(&temp, value->data, pool);
          if (err)
            return svn_error_create(SVN_ERR_BAD_PROPERTY_VALUE,
                                    err, NULL);
        }
    }

  return SVN_NO_ERROR;
}