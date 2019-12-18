#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {char* created_path; int /*<<< orphan*/  has_mergeinfo; scalar_t__ mergeinfo_count; int /*<<< orphan*/  is_fresh_txn_root; int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  copyfrom_rev; void* copyroot_path; int /*<<< orphan*/  copyroot_rev; int /*<<< orphan*/  id; int /*<<< orphan*/  predecessor_id; int /*<<< orphan*/  data_rep; int /*<<< orphan*/  prop_rep; scalar_t__ predecessor_count; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_COPYFROM ; 
 int /*<<< orphan*/  HEADER_COPYROOT ; 
 int /*<<< orphan*/  HEADER_COUNT ; 
 int /*<<< orphan*/  HEADER_CPATH ; 
 int /*<<< orphan*/  HEADER_FRESHTXNRT ; 
 int /*<<< orphan*/  HEADER_ID ; 
 int /*<<< orphan*/  HEADER_MINFO_CNT ; 
 int /*<<< orphan*/  HEADER_MINFO_HERE ; 
 int /*<<< orphan*/  HEADER_PRED ; 
 int /*<<< orphan*/  HEADER_PROPS ; 
 int /*<<< orphan*/  HEADER_TEXT ; 
 int /*<<< orphan*/  HEADER_TYPE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_FS_FS__KIND_DIR ; 
 int /*<<< orphan*/  SVN_FS_FS__KIND_FILE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parse_revnum (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  read_header_block (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_rep_offsets (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cstring_atoi (scalar_t__*,char*) ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_parse (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__id_rev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fspath__is_canonical (char*) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__read_noderev(node_revision_t **noderev_p,
                        svn_stream_t *stream,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  apr_hash_t *headers;
  node_revision_t *noderev;
  char *value;
  const char *noderev_id;

  SVN_ERR(read_header_block(&headers, stream, scratch_pool));

  noderev = apr_pcalloc(result_pool, sizeof(*noderev));

  /* Read the node-rev id. */
  value = svn_hash_gets(headers, HEADER_ID);
  if (value == NULL)
      /* ### More information: filename/offset coordinates */
      return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Missing id field in node-rev"));

  SVN_ERR(svn_stream_close(stream));

  SVN_ERR(svn_fs_fs__id_parse(&noderev->id, value, result_pool));
  noderev_id = value; /* for error messages later */

  /* Read the type. */
  value = svn_hash_gets(headers, HEADER_TYPE);

  if ((value == NULL) ||
      (   strcmp(value, SVN_FS_FS__KIND_FILE)
       && strcmp(value, SVN_FS_FS__KIND_DIR)))
    /* ### s/kind/type/ */
    return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                             _("Missing kind field in node-rev '%s'"),
                             noderev_id);

  noderev->kind = (strcmp(value, SVN_FS_FS__KIND_FILE) == 0)
                ? svn_node_file
                : svn_node_dir;

  /* Read the 'count' field. */
  value = svn_hash_gets(headers, HEADER_COUNT);
  if (value)
    SVN_ERR(svn_cstring_atoi(&noderev->predecessor_count, value));
  else
    noderev->predecessor_count = 0;

  /* Get the properties location. */
  value = svn_hash_gets(headers, HEADER_PROPS);
  if (value)
    {
      SVN_ERR(read_rep_offsets(&noderev->prop_rep, value,
                               noderev->id, result_pool, scratch_pool));
    }

  /* Get the data location. */
  value = svn_hash_gets(headers, HEADER_TEXT);
  if (value)
    {
      SVN_ERR(read_rep_offsets(&noderev->data_rep, value,
                               noderev->id, result_pool, scratch_pool));
    }

  /* Get the created path. */
  value = svn_hash_gets(headers, HEADER_CPATH);
  if (value == NULL)
    {
      return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                               _("Missing cpath field in node-rev '%s'"),
                               noderev_id);
    }
  else
    {
      if (!svn_fspath__is_canonical(value))
        return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                            _("Non-canonical cpath field in node-rev '%s'"),
                            noderev_id);

      noderev->created_path = apr_pstrdup(result_pool, value);
    }

  /* Get the predecessor ID. */
  value = svn_hash_gets(headers, HEADER_PRED);
  if (value)
    SVN_ERR(svn_fs_fs__id_parse(&noderev->predecessor_id, value,
                                result_pool));

  /* Get the copyroot. */
  value = svn_hash_gets(headers, HEADER_COPYROOT);
  if (value == NULL)
    {
      noderev->copyroot_path = apr_pstrdup(result_pool, noderev->created_path);
      noderev->copyroot_rev = svn_fs_fs__id_rev(noderev->id);
    }
  else
    {
      SVN_ERR(parse_revnum(&noderev->copyroot_rev, (const char **)&value));

      if (!svn_fspath__is_canonical(value))
        return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                                 _("Malformed copyroot line in node-rev '%s'"),
                                 noderev_id);
      noderev->copyroot_path = apr_pstrdup(result_pool, value);
    }

  /* Get the copyfrom. */
  value = svn_hash_gets(headers, HEADER_COPYFROM);
  if (value == NULL)
    {
      noderev->copyfrom_path = NULL;
      noderev->copyfrom_rev = SVN_INVALID_REVNUM;
    }
  else
    {
      SVN_ERR(parse_revnum(&noderev->copyfrom_rev, (const char **)&value));

      if (*value == 0)
        return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                                 _("Malformed copyfrom line in node-rev '%s'"),
                                 noderev_id);
      noderev->copyfrom_path = apr_pstrdup(result_pool, value);
    }

  /* Get whether this is a fresh txn root. */
  value = svn_hash_gets(headers, HEADER_FRESHTXNRT);
  noderev->is_fresh_txn_root = (value != NULL);

  /* Get the mergeinfo count. */
  value = svn_hash_gets(headers, HEADER_MINFO_CNT);
  if (value)
    SVN_ERR(svn_cstring_atoi64(&noderev->mergeinfo_count, value));
  else
    noderev->mergeinfo_count = 0;

  /* Get whether *this* node has mergeinfo. */
  value = svn_hash_gets(headers, HEADER_MINFO_HERE);
  noderev->has_mergeinfo = (value != NULL);

  *noderev_p = noderev;

  return SVN_NO_ERROR;
}