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
typedef  int svn_fs_path_change_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int kind; char* path; scalar_t__ noderev_id; scalar_t__ text_mod; scalar_t__ prop_mod; } ;
typedef  TYPE_2__ change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  is_valid_change_skel (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 TYPE_1__* svn_fs_base__id_unparse (scalar_t__,int /*<<< orphan*/ *) ; 
#define  svn_fs_path_change_add 132 
#define  svn_fs_path_change_delete 131 
#define  svn_fs_path_change_modify 130 
#define  svn_fs_path_change_replace 129 
#define  svn_fs_path_change_reset 128 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__mem_atom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__str_atom (char*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__unparse_change_skel(svn_skel_t **skel_p,
                                 const change_t *change,
                                 apr_pool_t *pool)
{
  svn_skel_t *skel;
  svn_string_t *tmp_str;
  svn_fs_path_change_kind_t kind;

  /* Create the skel. */
  skel = svn_skel__make_empty_list(pool);

  /* PROP-MOD */
  if (change->prop_mod)
    svn_skel__prepend(svn_skel__str_atom("1", pool), skel);
  else
    svn_skel__prepend(svn_skel__mem_atom(NULL, 0, pool), skel);

  /* TEXT-MOD */
  if (change->text_mod)
    svn_skel__prepend(svn_skel__str_atom("1", pool), skel);
  else
    svn_skel__prepend(svn_skel__mem_atom(NULL, 0, pool), skel);

  /* KIND */
  switch (change->kind)
    {
    case svn_fs_path_change_reset:
      svn_skel__prepend(svn_skel__str_atom("reset", pool), skel);
      break;
    case svn_fs_path_change_add:
      svn_skel__prepend(svn_skel__str_atom("add", pool), skel);
      break;
    case svn_fs_path_change_delete:
      svn_skel__prepend(svn_skel__str_atom("delete", pool), skel);
      break;
    case svn_fs_path_change_replace:
      svn_skel__prepend(svn_skel__str_atom("replace", pool), skel);
      break;
    case svn_fs_path_change_modify:
    default:
      svn_skel__prepend(svn_skel__str_atom("modify", pool), skel);
      break;
    }

  /* NODE-REV-ID */
  if (change->noderev_id)
    {
      tmp_str = svn_fs_base__id_unparse(change->noderev_id, pool);
      svn_skel__prepend(svn_skel__mem_atom(tmp_str->data, tmp_str->len, pool),
                        skel);
    }
  else
    {
      svn_skel__prepend(svn_skel__mem_atom(NULL, 0, pool), skel);
    }

  /* PATH */
  svn_skel__prepend(svn_skel__str_atom(change->path, pool), skel);

  /* "change" */
  svn_skel__prepend(svn_skel__str_atom("change", pool), skel);

  /* Validate and return the skel. */
  if (! is_valid_change_skel(skel, &kind))
    return skel_err("change");
  if (kind != change->kind)
    return skel_err("change");
  *skel_p = skel;
  return SVN_NO_ERROR;
}