#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {char* txn_id; } ;
typedef  TYPE_1__ revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  is_valid_revision_skel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__str_atom (char*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__unparse_revision_skel(svn_skel_t **skel_p,
                                   const revision_t *revision,
                                   apr_pool_t *pool)
{
  svn_skel_t *skel;

  /* Create the skel. */
  skel = svn_skel__make_empty_list(pool);

  /* TXN_ID */
  svn_skel__prepend(svn_skel__str_atom(revision->txn_id, pool), skel);

  /* "revision" */
  svn_skel__prepend(svn_skel__str_atom("revision", pool), skel);

  /* Validate and return the skel. */
  if (! is_valid_revision_skel(skel))
    return skel_err("revision");
  *skel_p = skel;
  return SVN_NO_ERROR;
}