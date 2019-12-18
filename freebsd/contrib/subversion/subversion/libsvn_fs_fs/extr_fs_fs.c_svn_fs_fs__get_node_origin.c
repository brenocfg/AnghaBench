#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_7__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_2__ svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_hash_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_node_origins_from_file (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn__ui64tobase36 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_parse (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_node_origin (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__get_node_origin(const svn_fs_id_t **origin_id,
                           svn_fs_t *fs,
                           const svn_fs_fs__id_part_t *node_id,
                           apr_pool_t *pool)
{
  apr_hash_t *node_origins;

  *origin_id = NULL;
  SVN_ERR(get_node_origins_from_file(fs, &node_origins,
                                     svn_fs_fs__path_node_origin(fs, node_id,
                                                                 pool),
                                     pool));
  if (node_origins)
    {
      char node_id_ptr[SVN_INT64_BUFFER_SIZE];
      apr_size_t len = svn__ui64tobase36(node_id_ptr, node_id->number);
      svn_string_t *origin_id_str
        = apr_hash_get(node_origins, node_id_ptr, len);

      if (origin_id_str)
        SVN_ERR(svn_fs_fs__id_parse(origin_id,
                                    apr_pstrdup(pool, origin_id_str->data),
                                    pool));
    }
  return SVN_NO_ERROR;
}