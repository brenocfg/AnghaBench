#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ svn_string_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_stringbuf_createf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_stringbuf_t *
generate_conflict_message(const char *propname,
                          const svn_string_t *original,
                          const svn_string_t *mine,
                          const svn_string_t *incoming,
                          const svn_string_t *incoming_base,
                          apr_pool_t *result_pool)
{
  if (incoming_base == NULL)
    {
      /* Attempting to add the value INCOMING.  */
      SVN_ERR_ASSERT_NO_RETURN(incoming != NULL);

      if (mine)
        {
          /* To have a conflict, these must be different.  */
          SVN_ERR_ASSERT_NO_RETURN(!svn_string_compare(mine, incoming));

          /* Note that we don't care whether MINE is locally-added or
             edited, or just something different that is a copy of the
             pristine ORIGINAL.  */
          return svn_stringbuf_createf(result_pool,
                                       _("Trying to add new property '%s'\n"
                                         "but the property already exists.\n"),
                                       propname);
        }

      /* To have a conflict, we must have an ORIGINAL which has been
         locally-deleted.  */
      SVN_ERR_ASSERT_NO_RETURN(original != NULL);
      return svn_stringbuf_createf(result_pool,
                                   _("Trying to add new property '%s'\n"
                                     "but the property has been locally "
                                     "deleted.\n"),
                                   propname);
    }

  if (incoming == NULL)
    {
      /* Attempting to delete the value INCOMING_BASE.  */
      SVN_ERR_ASSERT_NO_RETURN(incoming_base != NULL);

      /* Are we trying to delete a local addition? */
      if (original == NULL && mine != NULL)
        return svn_stringbuf_createf(result_pool,
                                     _("Trying to delete property '%s'\n"
                                       "but the property has been locally "
                                       "added.\n"),
                                     propname);

      /* A conflict can only occur if we originally had the property;
         otherwise, we would have merged the property-delete into the
         non-existent property.  */
      SVN_ERR_ASSERT_NO_RETURN(original != NULL);

      if (svn_string_compare(original, incoming_base))
        {
          if (mine)
            /* We were trying to delete the correct property, but an edit
               caused the conflict.  */
            return svn_stringbuf_createf(result_pool,
                                         _("Trying to delete property '%s'\n"
                                           "but the property has been locally "
                                           "modified.\n"),
                                         propname);
        }
      else if (mine == NULL)
        {
          /* We were trying to delete the property, but we have locally
             deleted the same property, but with a different value. */
          return svn_stringbuf_createf(result_pool,
                                       _("Trying to delete property '%s'\n"
                                         "but the property has been locally "
                                         "deleted and had a different "
                                         "value.\n"),
                                       propname);
        }

      /* We were trying to delete INCOMING_BASE but our ORIGINAL is
         something else entirely.  */
      SVN_ERR_ASSERT_NO_RETURN(!svn_string_compare(original, incoming_base));

      return svn_stringbuf_createf(result_pool,
                                   _("Trying to delete property '%s'\n"
                                     "but the local property value is "
                                     "different.\n"),
                                   propname);
    }

  /* Attempting to change the property from INCOMING_BASE to INCOMING.  */

  /* If we have a (current) property value, then it should be different
     from the INCOMING_BASE; otherwise, the incoming change would have
     been applied to it.  */
  SVN_ERR_ASSERT_NO_RETURN(!mine || !svn_string_compare(mine, incoming_base));

  if (original && mine && svn_string_compare(original, mine))
    {
      /* We have an unchanged property, so the original values must
         have been different.  */
      SVN_ERR_ASSERT_NO_RETURN(!svn_string_compare(original, incoming_base));
      return svn_stringbuf_createf(result_pool,
                                   _("Trying to change property '%s'\n"
                                     "but the local property value conflicts "
                                     "with the incoming change.\n"),
                                   propname);
    }

  if (original && mine)
    return svn_stringbuf_createf(result_pool,
                                 _("Trying to change property '%s'\n"
                                   "but the property has already been locally "
                                   "changed to a different value.\n"),
                                 propname);

  if (original)
    return svn_stringbuf_createf(result_pool,
                                 _("Trying to change property '%s'\nbut "
                                   "the property has been locally deleted.\n"),
                                 propname);

  if (mine)
    return svn_stringbuf_createf(result_pool,
                                 _("Trying to change property '%s'\nbut the "
                                   "property has been locally added with a "
                                   "different value.\n"),
                                 propname);

  return svn_stringbuf_createf(result_pool,
                               _("Trying to change property '%s'\nbut "
                                 "the property does not exist locally.\n"),
                               propname);
}