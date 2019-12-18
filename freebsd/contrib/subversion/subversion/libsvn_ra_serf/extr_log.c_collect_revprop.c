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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_RA_DAV_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * svn_base64_decode_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
collect_revprop(apr_hash_t *revprops,
                const char *propname,
                const svn_string_t *cdata,
                const char *encoding)
{
  apr_pool_t *result_pool = apr_hash_pool_get(revprops);
  const svn_string_t *decoded;

  if (encoding)
    {
      /* Check for a known encoding type.  This is easy -- there's
         only one.  */
      if (strcmp(encoding, "base64") != 0)
        {
          return svn_error_createf(SVN_ERR_RA_DAV_MALFORMED_DATA, NULL,
                                   _("Unsupported encoding '%s'"),
                                   encoding);
        }

      decoded = svn_base64_decode_string(cdata, result_pool);
    }
  else
    {
      decoded = svn_string_dup(cdata, result_pool);
    }

  /* Caller has ensured PROPNAME has sufficient lifetime.  */
  svn_hash_sets(revprops, propname, decoded);

  return SVN_NO_ERROR;
}