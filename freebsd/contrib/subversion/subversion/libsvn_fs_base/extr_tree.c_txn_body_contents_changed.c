#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct things_changed_args {int* changed_p; int /*<<< orphan*/  strict; int /*<<< orphan*/  path2; int /*<<< orphan*/  root2; int /*<<< orphan*/  path1; int /*<<< orphan*/  root1; } ;
typedef  int /*<<< orphan*/  dag_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_fs_base__dag_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__things_different (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_contents_same2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_contents_changed(void *baton, trail_t *trail)
{
  struct things_changed_args *args = baton;
  dag_node_t *node1, *node2;
  svn_checksum_t *checksum1, *checksum2;
  svn_stream_t *stream1, *stream2;
  svn_boolean_t same;

  SVN_ERR(get_dag(&node1, args->root1, args->path1, trail, trail->pool));
  SVN_ERR(get_dag(&node2, args->root2, args->path2, trail, trail->pool));
  SVN_ERR(svn_fs_base__things_different(NULL, args->changed_p,
                                        node1, node2, trail, trail->pool));

  /* Is there a potential false positive and do we want to correct it? */
  if (!args->strict || !*args->changed_p)
    return SVN_NO_ERROR;

  /* Different representations. They might still have equal contents. */

  /* Compare MD5 checksums.  These should be readily accessible. */
  SVN_ERR(svn_fs_base__dag_file_checksum(&checksum1, svn_checksum_md5,
                                         node1, trail, trail->pool));
  SVN_ERR(svn_fs_base__dag_file_checksum(&checksum2, svn_checksum_md5,
                                         node2, trail, trail->pool));

  /* Different MD5 checksums -> different contents */
  if (!svn_checksum_match(checksum1, checksum2))
    return SVN_NO_ERROR;

  /* Paranoia. Compare SHA1 checksums because that's the level of
     confidence we require for e.g. the working copy. */
  SVN_ERR(svn_fs_base__dag_file_checksum(&checksum1, svn_checksum_sha1,
                                         node1, trail, trail->pool));
  SVN_ERR(svn_fs_base__dag_file_checksum(&checksum2, svn_checksum_sha1,
                                         node2, trail, trail->pool));

  /* Different SHA1 checksums -> different contents */
  if (checksum1 && checksum2)
    {
      *args->changed_p = !svn_checksum_match(checksum1, checksum2);
      return SVN_NO_ERROR;
    }

  /* SHA1 checksums are not available for very old reps / repositories. */
  SVN_ERR(svn_fs_base__dag_get_contents(&stream1, node1, trail, trail->pool));
  SVN_ERR(svn_fs_base__dag_get_contents(&stream2, node2, trail, trail->pool));
  SVN_ERR(svn_stream_contents_same2(&same, stream1, stream2, trail->pool));

  /* Now, it's definitive. */
  *args->changed_p = !same;
  return SVN_NO_ERROR;
}