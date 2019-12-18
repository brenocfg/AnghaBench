#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_6__ {int /*<<< orphan*/  has_mergeinfo; scalar_t__ mergeinfo_count; int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  copyfrom_rev; void* copyroot_path; int /*<<< orphan*/  copyroot_rev; TYPE_3__ noderev_id; void* created_path; int /*<<< orphan*/  predecessor_id; int /*<<< orphan*/  data_rep; int /*<<< orphan*/  prop_rep; scalar_t__ predecessor_count; int /*<<< orphan*/  kind; TYPE_3__ copy_id; TYPE_3__ node_id; } ;
typedef  TYPE_1__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_COPY ; 
 int /*<<< orphan*/  HEADER_COPYFROM ; 
 int /*<<< orphan*/  HEADER_COPYROOT ; 
 int /*<<< orphan*/  HEADER_COUNT ; 
 int /*<<< orphan*/  HEADER_CPATH ; 
 int /*<<< orphan*/  HEADER_ID ; 
 int /*<<< orphan*/  HEADER_MINFO_CNT ; 
 int /*<<< orphan*/  HEADER_MINFO_HERE ; 
 int /*<<< orphan*/  HEADER_NODE ; 
 int /*<<< orphan*/  HEADER_PRED ; 
 int /*<<< orphan*/  HEADER_PROPS ; 
 int /*<<< orphan*/  HEADER_TEXT ; 
 int /*<<< orphan*/  HEADER_TYPE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_FS_X__KIND_DIR ; 
 int /*<<< orphan*/  SVN_FS_X__KIND_FILE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char*) ; 
 void* auto_unescape_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_revnum (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  read_header_block (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_id_part (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_rep_offsets (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cstring_atoi (scalar_t__*,char*) ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__id_parse (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_x__id_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__is_canonical (char*) ; 
 void* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__read_noderev(svn_fs_x__noderev_t **noderev_p,
                       svn_stream_t *stream,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  apr_hash_t *headers;
  svn_fs_x__noderev_t *noderev;
  char *value;
  const char *noderev_id;

  SVN_ERR(read_header_block(&headers, stream, scratch_pool));
  SVN_ERR(svn_stream_close(stream));

  noderev = apr_pcalloc(result_pool, sizeof(*noderev));

  /* for error messages later */
  noderev_id = svn_hash_gets(headers, HEADER_ID);

  /* Read the node-rev id. */
  SVN_ERR(read_id_part(&noderev->noderev_id, headers, HEADER_ID));
  SVN_ERR(read_id_part(&noderev->node_id, headers, HEADER_NODE));
  SVN_ERR(read_id_part(&noderev->copy_id, headers, HEADER_COPY));

  /* Read the type. */
  value = svn_hash_gets(headers, HEADER_TYPE);

  if ((value == NULL) ||
      (   strcmp(value, SVN_FS_X__KIND_FILE)
       && strcmp(value, SVN_FS_X__KIND_DIR)))
    /* ### s/kind/type/ */
    return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                             _("Missing kind field in node-rev '%s'"),
                             noderev_id);

  noderev->kind = (strcmp(value, SVN_FS_X__KIND_FILE) == 0)
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
                               &noderev->noderev_id, result_pool,
                               scratch_pool));
    }

  /* Get the data location. */
  value = svn_hash_gets(headers, HEADER_TEXT);
  if (value)
    {
      SVN_ERR(read_rep_offsets(&noderev->data_rep, value,
                               &noderev->noderev_id, result_pool,
                               scratch_pool));
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

      noderev->created_path = auto_unescape_path(apr_pstrdup(result_pool,
                                                              value),
                                                 result_pool);
    }

  /* Get the predecessor ID. */
  value = svn_hash_gets(headers, HEADER_PRED);
  if (value)
    SVN_ERR(svn_fs_x__id_parse(&noderev->predecessor_id, value));
  else
    svn_fs_x__id_reset(&noderev->predecessor_id);

  /* Get the copyroot. */
  value = svn_hash_gets(headers, HEADER_COPYROOT);
  if (value == NULL)
    {
      noderev->copyroot_path = noderev->created_path;
      noderev->copyroot_rev
        = svn_fs_x__get_revnum(noderev->noderev_id.change_set);
    }
  else
    {
      SVN_ERR(parse_revnum(&noderev->copyroot_rev, (const char **)&value));

      if (!svn_fspath__is_canonical(value))
        return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                                 _("Malformed copyroot line in node-rev '%s'"),
                                 noderev_id);
      noderev->copyroot_path = auto_unescape_path(apr_pstrdup(result_pool,
                                                              value),
                                                  result_pool);
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
      noderev->copyfrom_path = auto_unescape_path(apr_pstrdup(result_pool,
                                                              value),
                                                  result_pool);
    }

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