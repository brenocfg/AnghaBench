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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  size_t svn_checksum_kind_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_KIND ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CHECKSUM_PARSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 char const** ckind_str ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,scalar_t__) ; 
 size_t svn_checksum_fnv1a_32x4 ; 
 size_t svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,size_t,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 

svn_error_t *
svn_checksum_deserialize(const svn_checksum_t **checksum,
                         const char *data,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  svn_checksum_kind_t kind;
  svn_checksum_t *parsed_checksum;

  /* All prefixes have the same length. */
  apr_size_t prefix_len = strlen(ckind_str[0]);

  /* "$md5 $...", "$sha1$..." or ... */
  if (strlen(data) <= prefix_len)
    return svn_error_createf(SVN_ERR_BAD_CHECKSUM_PARSE, NULL,
                             _("Invalid prefix in checksum '%s'"),
                             data);

  for (kind = svn_checksum_md5; kind <= svn_checksum_fnv1a_32x4; ++kind)
    if (strncmp(ckind_str[kind], data, prefix_len) == 0)
      {
        SVN_ERR(svn_checksum_parse_hex(&parsed_checksum, kind,
                                       data + prefix_len, result_pool));
        *checksum = parsed_checksum;
        return SVN_NO_ERROR;
      }

  return svn_error_createf(SVN_ERR_BAD_CHECKSUM_KIND, NULL,
                           "Unknown checksum kind in '%s'", data);
}