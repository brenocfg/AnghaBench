#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
struct TYPE_9__ {int change_set; scalar_t__ number; } ;
struct TYPE_11__ {int /*<<< orphan*/  sha1_digest; int /*<<< orphan*/  has_sha1; int /*<<< orphan*/  md5_digest; void* expanded_size; void* size; TYPE_1__ id; } ;
typedef  TYPE_3__ svn_fs_x__representation_t ;
typedef  void* svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_4__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int apr_int64_t ;

/* Variables and functions */
 int APR_MD5_DIGESTSIZE ; 
 int APR_SHA1_DIGESTSIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int SVN_FS_X__INVALID_CHANGE_SET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (TYPE_4__**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (int*,char*) ; 
 char* svn_cstring_tokenize (char*,char**) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__parse_representation(svn_fs_x__representation_t **rep_p,
                               svn_stringbuf_t *text,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  svn_fs_x__representation_t *rep;
  char *str;
  apr_int64_t val;
  char *string = text->data;
  svn_checksum_t *checksum;

  rep = apr_pcalloc(result_pool, sizeof(*rep));
  *rep_p = rep;

  str = svn_cstring_tokenize(" ", &string);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Malformed text representation offset line in node-rev"));

  SVN_ERR(svn_cstring_atoi64(&rep->id.change_set, str));

  /* while in transactions, it is legal to simply write "-1" */
  if (rep->id.change_set == -1)
    return SVN_NO_ERROR;

  str = svn_cstring_tokenize(" ", &string);
  if (str == NULL)
    {
      if (rep->id.change_set == SVN_FS_X__INVALID_CHANGE_SET)
        return SVN_NO_ERROR;

      return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Malformed text representation offset line in node-rev"));
    }

  SVN_ERR(svn_cstring_atoi64(&val, str));
  rep->id.number = (apr_off_t)val;

  str = svn_cstring_tokenize(" ", &string);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Malformed text representation offset line in node-rev"));

  SVN_ERR(svn_cstring_atoi64(&val, str));
  rep->size = (svn_filesize_t)val;

  str = svn_cstring_tokenize(" ", &string);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Malformed text representation offset line in node-rev"));

  SVN_ERR(svn_cstring_atoi64(&val, str));
  rep->expanded_size = (svn_filesize_t)val;

  /* Read in the MD5 hash. */
  str = svn_cstring_tokenize(" ", &string);
  if ((str == NULL) || (strlen(str) != (APR_MD5_DIGESTSIZE * 2)))
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Malformed text representation offset line in node-rev"));

  SVN_ERR(svn_checksum_parse_hex(&checksum, svn_checksum_md5, str,
                                 scratch_pool));
  if (checksum)
    memcpy(rep->md5_digest, checksum->digest, sizeof(rep->md5_digest));

  /* The remaining fields are only used for formats >= 4, so check that. */
  str = svn_cstring_tokenize(" ", &string);
  if (str == NULL)
    return SVN_NO_ERROR;

  /* Read the SHA1 hash. */
  if (strlen(str) != (APR_SHA1_DIGESTSIZE * 2))
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Malformed text representation offset line in node-rev"));

  SVN_ERR(svn_checksum_parse_hex(&checksum, svn_checksum_sha1, str,
                                 scratch_pool));
  rep->has_sha1 = checksum != NULL;
  if (checksum)
    memcpy(rep->sha1_digest, checksum->digest, sizeof(rep->sha1_digest));

  return SVN_NO_ERROR;
}