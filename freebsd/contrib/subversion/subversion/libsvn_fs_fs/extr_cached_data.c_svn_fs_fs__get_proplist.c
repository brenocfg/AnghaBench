#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_16__ {TYPE_6__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_17__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  item_index; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_3__ representation_t ;
struct TYPE_18__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ pair_cache_key_t ;
struct TYPE_19__ {int /*<<< orphan*/  id; TYPE_3__* prop_rep; } ;
typedef  TYPE_5__ node_revision_t ;
struct TYPE_20__ {scalar_t__ properties_cache; } ;
typedef  TYPE_6__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,scalar_t__,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (scalar_t__,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_quick_wrapf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_fs_fs__get_contents (int /*<<< orphan*/ **,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__id_txn_used (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_fs_fs__id_unparse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_txn_node_props (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__get_proplist(apr_hash_t **proplist_p,
                        svn_fs_t *fs,
                        node_revision_t *noderev,
                        apr_pool_t *pool)
{
  apr_hash_t *proplist;
  svn_stream_t *stream;

  if (noderev->prop_rep && svn_fs_fs__id_txn_used(&noderev->prop_rep->txn_id))
    {
      svn_error_t *err;
      const char *filename
        = svn_fs_fs__path_txn_node_props(fs, noderev->id, pool);
      proplist = apr_hash_make(pool);

      SVN_ERR(svn_stream_open_readonly(&stream, filename, pool, pool));
      err = svn_hash_read2(proplist, stream, SVN_HASH_TERMINATOR, pool);
      if (err)
        {
          svn_string_t *id_str = svn_fs_fs__id_unparse(noderev->id, pool);

          err = svn_error_compose_create(err, svn_stream_close(stream));
          return svn_error_quick_wrapf(err,
                   _("malformed property list for node-revision '%s' in '%s'"),
                   id_str->data, filename);
        }
      SVN_ERR(svn_stream_close(stream));
    }
  else if (noderev->prop_rep)
    {
      svn_error_t *err;
      fs_fs_data_t *ffd = fs->fsap_data;
      representation_t *rep = noderev->prop_rep;
      pair_cache_key_t key = { 0 };

      key.revision = rep->revision;
      key.second = rep->item_index;
      if (ffd->properties_cache && SVN_IS_VALID_REVNUM(rep->revision))
        {
          svn_boolean_t is_cached;
          SVN_ERR(svn_cache__get((void **) proplist_p, &is_cached,
                                 ffd->properties_cache, &key, pool));
          if (is_cached)
            return SVN_NO_ERROR;
        }

      proplist = apr_hash_make(pool);
      SVN_ERR(svn_fs_fs__get_contents(&stream, fs, noderev->prop_rep, FALSE,
                                      pool));
      err = svn_hash_read2(proplist, stream, SVN_HASH_TERMINATOR, pool);
      if (err)
        {
          svn_string_t *id_str = svn_fs_fs__id_unparse(noderev->id, pool);

          err = svn_error_compose_create(err, svn_stream_close(stream));
          return svn_error_quick_wrapf(err,
                   _("malformed property list for node-revision '%s'"),
                   id_str->data);
        }
      SVN_ERR(svn_stream_close(stream));

      if (ffd->properties_cache && SVN_IS_VALID_REVNUM(rep->revision))
        SVN_ERR(svn_cache__set(ffd->properties_cache, &key, proplist, pool));
    }
  else
    {
      /* return an empty prop list if the node doesn't have any props */
      proplist = apr_hash_make(pool);
    }

  *proplist_p = proplist;

  return SVN_NO_ERROR;
}