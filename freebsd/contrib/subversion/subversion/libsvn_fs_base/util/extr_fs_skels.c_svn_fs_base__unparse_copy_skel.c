#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {char* src_txn_id; char* src_path; scalar_t__ kind; int /*<<< orphan*/  dst_noderev_id; } ;
typedef  TYPE_2__ copy_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ copy_kind_real ; 
 int /*<<< orphan*/  is_valid_copy_skel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 TYPE_1__* svn_fs_base__id_unparse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__mem_atom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__str_atom (char*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__unparse_copy_skel(svn_skel_t **skel_p,
                               const copy_t *copy,
                               apr_pool_t *pool)
{
  svn_skel_t *skel;
  svn_string_t *tmp_str;

  /* Create the skel. */
  skel = svn_skel__make_empty_list(pool);

  /* DST-NODE-ID */
  tmp_str = svn_fs_base__id_unparse(copy->dst_noderev_id, pool);
  svn_skel__prepend(svn_skel__mem_atom(tmp_str->data, tmp_str->len, pool),
                    skel);

  /* SRC-TXN-ID */
  if ((copy->src_txn_id) && (*copy->src_txn_id))
    svn_skel__prepend(svn_skel__str_atom(copy->src_txn_id, pool), skel);
  else
    svn_skel__prepend(svn_skel__mem_atom(NULL, 0, pool), skel);

  /* SRC-PATH */
  if ((copy->src_path) && (*copy->src_path))
    svn_skel__prepend(svn_skel__str_atom(copy->src_path, pool), skel);
  else
    svn_skel__prepend(svn_skel__mem_atom(NULL, 0, pool), skel);

  /* "copy" */
  if (copy->kind == copy_kind_real)
    svn_skel__prepend(svn_skel__str_atom("copy", pool), skel);
  else
    svn_skel__prepend(svn_skel__str_atom("soft-copy", pool), skel);

  /* Validate and return the skel. */
  if (! is_valid_copy_skel(skel))
    return skel_err("copy");
  *skel_p = skel;
  return SVN_NO_ERROR;
}