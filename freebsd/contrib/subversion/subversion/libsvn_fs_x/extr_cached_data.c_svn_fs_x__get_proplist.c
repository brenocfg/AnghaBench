#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_15__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
struct TYPE_16__ {int /*<<< orphan*/  expanded_size; TYPE_1__ id; } ;
typedef  TYPE_2__ svn_fs_x__representation_t ;
struct TYPE_17__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ svn_fs_x__pair_cache_key_t ;
struct TYPE_18__ {int /*<<< orphan*/  noderev_id; TYPE_2__* prop_rep; } ;
typedef  TYPE_4__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
struct TYPE_19__ {int /*<<< orphan*/  properties_cache; } ;
typedef  TYPE_5__ svn_fs_x__data_t ;
struct TYPE_20__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_6__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_21__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_contents (int /*<<< orphan*/ **,TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 TYPE_8__* svn_fs_x__id_unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_revision (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__parse_properties (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_txn_node_props (TYPE_6__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_from_stream2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_from_file2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__get_proplist(apr_hash_t **proplist,
                       svn_fs_t *fs,
                       svn_fs_x__noderev_t *noderev,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  svn_stream_t *stream;
  const svn_fs_x__id_t *noderev_id = &noderev->noderev_id;

  if (noderev->prop_rep
      && !svn_fs_x__is_revision(noderev->prop_rep->id.change_set))
    {
      svn_stringbuf_t *content;
      svn_string_t *as_string;
      const char *filename = svn_fs_x__path_txn_node_props(fs, noderev_id,
                                                           scratch_pool,
                                                           scratch_pool);
      SVN_ERR(svn_stringbuf_from_file2(&content, filename, result_pool));

      as_string = svn_stringbuf__morph_into_string(content);
      SVN_ERR_W(svn_fs_x__parse_properties(proplist, as_string, result_pool),
                apr_psprintf(scratch_pool,
                    "malformed property list for node-revision '%s' in '%s'",
                    svn_fs_x__id_unparse(&noderev->noderev_id,
                                         scratch_pool)->data,
                    filename));
    }
  else if (noderev->prop_rep)
    {
      svn_fs_x__data_t *ffd = fs->fsap_data;
      svn_fs_x__representation_t *rep = noderev->prop_rep;
      svn_fs_x__pair_cache_key_t key = { 0 };
      svn_string_t *content;
      svn_boolean_t is_cached;

      key.revision = svn_fs_x__get_revnum(rep->id.change_set);
      key.second = rep->id.number;
      SVN_ERR(svn_cache__get((void **) proplist, &is_cached,
                             ffd->properties_cache, &key, result_pool));
      if (is_cached)
        return SVN_NO_ERROR;

      SVN_ERR(svn_fs_x__get_contents(&stream, fs, rep, FALSE, scratch_pool));
      SVN_ERR(svn_string_from_stream2(&content, stream, rep->expanded_size,
                                      result_pool));

      SVN_ERR_W(svn_fs_x__parse_properties(proplist, content, result_pool),
                apr_psprintf(scratch_pool,
                    "malformed property list for node-revision '%s'",
                    svn_fs_x__id_unparse(&noderev->noderev_id,
                                         scratch_pool)->data));

      SVN_ERR(svn_cache__set(ffd->properties_cache, &key, *proplist,
                             scratch_pool));
    }
  else
    {
      /* return an empty prop list if the node doesn't have any props */
      *proplist = apr_hash_make(result_pool);
    }

  return SVN_NO_ERROR;
}