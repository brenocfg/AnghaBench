#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* data; int len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_uint64_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  scalar_t__ apr_byte_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT_PROPLIST ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char const*,int,TYPE_1__*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 
 scalar_t__* svn__decode_uint (int*,scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

svn_error_t *
svn_fs_x__parse_properties(apr_hash_t **properties,
                           const svn_string_t *content,
                           apr_pool_t *result_pool)
{
  const apr_byte_t *p = (const apr_byte_t *)content->data;
  const apr_byte_t *end = p + content->len;
  apr_uint64_t count;

  *properties = apr_hash_make(result_pool);

  /* Extract the number of properties we are expected to read. */
  p = svn__decode_uint(&count, p, end);

  /* Read all the properties we find.
     Because prop-name and prop-value are nicely NUL-terminated
     sub-strings of CONTENT, we can simply reference them there.
     I.e. there is no need to copy them around.
   */
  while (p < end)
    {
      apr_uint64_t value_len;
      svn_string_t *value;

      const char *key = (const char *)p;

      /* Note that this may never overflow / segfault because
         CONTENT itself is NUL-terminated. */
      apr_size_t key_len = strlen(key);
      p += key_len + 1;
      if (key[key_len])
        return svn_error_createf(SVN_ERR_FS_CORRUPT_PROPLIST, NULL,
                                 "Property name not NUL terminated");

      if (p >= end)
        return svn_error_createf(SVN_ERR_FS_CORRUPT_PROPLIST, NULL,
                                 "Property value missing");
      p = svn__decode_uint(&value_len, p, end);
      if (value_len >= (end - p))
        return svn_error_createf(SVN_ERR_FS_CORRUPT_PROPLIST, NULL,
                                 "Property value too long");

      value = apr_pcalloc(result_pool, sizeof(*value));
      value->data = (const char *)p;
      value->len = (apr_size_t)value_len;
      if (p[value->len])
        return svn_error_createf(SVN_ERR_FS_CORRUPT_PROPLIST, NULL,
                                 "Property value not NUL terminated");

      p += value->len + 1;

      apr_hash_set(*properties, key, key_len, value);
    }

  /* Check that we read the expected number of properties. */
  if ((apr_uint64_t)apr_hash_count(*properties) != count)
    return svn_error_createf(SVN_ERR_FS_CORRUPT_PROPLIST, NULL,
                             "Property count mismatch");

  return SVN_NO_ERROR;
}