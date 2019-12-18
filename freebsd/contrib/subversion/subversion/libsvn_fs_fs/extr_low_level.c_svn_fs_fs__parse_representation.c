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
typedef  void* svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_3__ svn_checksum_t ;
struct TYPE_9__ {int /*<<< orphan*/  number; int /*<<< orphan*/  noderev_txn_id; } ;
struct TYPE_12__ {scalar_t__ revision; TYPE_1__ uniquifier; int /*<<< orphan*/  sha1_digest; int /*<<< orphan*/  has_sha1; int /*<<< orphan*/  md5_digest; void* expanded_size; void* size; scalar_t__ item_index; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_4__ representation_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int APR_MD5_DIGESTSIZE ; 
 int APR_SHA1_DIGESTSIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_revnum (scalar_t__*,char const**) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  svn__base36toui64 (char const**,char*) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (TYPE_3__**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,char*) ; 
 char* svn_cstring_tokenize (char*,char**) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_parse (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_reset (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__parse_representation(representation_t **rep_p,
                                svn_stringbuf_t *text,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  representation_t *rep;
  char *str;
  apr_int64_t val;
  char *string = text->data;
  svn_checksum_t *checksum;
  const char *end;

  rep = apr_pcalloc(result_pool, sizeof(*rep));
  *rep_p = rep;

  SVN_ERR(parse_revnum(&rep->revision, (const char **)&string));

  /* initialize transaction info (never stored) */
  svn_fs_fs__id_txn_reset(&rep->txn_id);

  /* while in transactions, it is legal to simply write "-1" */
  str = svn_cstring_tokenize(" ", &string);
  if (str == NULL)
    {
      if (rep->revision == SVN_INVALID_REVNUM)
        return SVN_NO_ERROR;

      return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Malformed text representation offset line in node-rev"));
    }

  SVN_ERR(svn_cstring_atoi64(&val, str));
  rep->item_index = (apr_uint64_t)val;

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

  /* If STR is a all-zero checksum, CHECKSUM will be NULL and REP already
     contains the correct value. */
  if (checksum)
    memcpy(rep->md5_digest, checksum->digest, sizeof(rep->md5_digest));

  /* The remaining fields are only used for formats >= 4, so check that. */
  str = svn_cstring_tokenize(" ", &string);
  if (str == NULL)
    return SVN_NO_ERROR;

  /* Is the SHA1 hash present? */
  if (str[0] == '-' && str[1] == 0)
    {
      checksum = NULL;
    }
  else
    {
      /* Read the SHA1 hash. */
      if (strlen(str) != (APR_SHA1_DIGESTSIZE * 2))
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Malformed text representation offset line in node-rev"));

      SVN_ERR(svn_checksum_parse_hex(&checksum, svn_checksum_sha1, str,
                                     scratch_pool));
    }

  /* We do have a valid SHA1 but it might be all 0.
     We cannot be sure where that came from (Alas! legacy), so let's not
     claim we know the SHA1 in that case. */
  rep->has_sha1 = checksum != NULL;

  /* If STR is a all-zero checksum, CHECKSUM will be NULL and REP already
     contains the correct value. */
  if (checksum)
    memcpy(rep->sha1_digest, checksum->digest, sizeof(rep->sha1_digest));

  str = svn_cstring_tokenize(" ", &string);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Malformed text representation offset line in node-rev"));

  /* Is the uniquifier present? */
  if (str[0] == '-' && str[1] == 0)
    {
      end = string;
    }
  else
    {
      char *substring = str;

      /* Read the uniquifier. */
      str = svn_cstring_tokenize("/", &substring);
      if (str == NULL)
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Malformed text representation offset line in node-rev"));

      SVN_ERR(svn_fs_fs__id_txn_parse(&rep->uniquifier.noderev_txn_id, str));

      str = svn_cstring_tokenize(" ", &substring);
      if (str == NULL || *str != '_')
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Malformed text representation offset line in node-rev"));

      ++str;
      rep->uniquifier.number = svn__base36toui64(&end, str);
    }

  if (*end)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Malformed text representation offset line in node-rev"));

  return SVN_NO_ERROR;
}