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
struct TYPE_3__ {char* comment; char* owner; char* token; char* path; scalar_t__ is_dav_comment; scalar_t__ creation_date; scalar_t__ expiration_date; } ;
typedef  TYPE_1__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  is_valid_lock_skel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__mem_atom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__str_atom (char*,int /*<<< orphan*/ *) ; 
 char* svn_time_to_cstring (scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__unparse_lock_skel(svn_skel_t **skel_p,
                               const svn_lock_t *lock,
                               apr_pool_t *pool)
{
  svn_skel_t *skel;

  /* Create the skel. */
  skel = svn_skel__make_empty_list(pool);

  /* EXP-DATE is optional.  If not present, just use an empty atom. */
  if (lock->expiration_date)
    svn_skel__prepend(svn_skel__str_atom(
                          svn_time_to_cstring(lock->expiration_date, pool),
                          pool), skel);
  else
    svn_skel__prepend(svn_skel__mem_atom(NULL, 0, pool), skel);

  /* CREATION-DATE */
  svn_skel__prepend(svn_skel__str_atom(
                        svn_time_to_cstring(lock->creation_date, pool),
                        pool), skel);

  /* XML_P */
  if (lock->is_dav_comment)
    svn_skel__prepend(svn_skel__str_atom("1", pool), skel);
  else
    svn_skel__prepend(svn_skel__str_atom("0", pool), skel);

  /* COMMENT */
  if (lock->comment)
    svn_skel__prepend(svn_skel__str_atom(lock->comment, pool), skel);
  else
    svn_skel__prepend(svn_skel__mem_atom(NULL, 0, pool), skel);

  /* OWNER */
  svn_skel__prepend(svn_skel__str_atom(lock->owner, pool), skel);

  /* LOCK-TOKEN */
  svn_skel__prepend(svn_skel__str_atom(lock->token, pool), skel);

  /* PATH */
  svn_skel__prepend(svn_skel__str_atom(lock->path, pool), skel);

  /* "lock" */
  svn_skel__prepend(svn_skel__str_atom("lock", pool), skel);

  /* Validate and return the skel. */
  if (! is_valid_lock_skel(skel))
    return skel_err("lock");

  *skel_p = skel;
  return SVN_NO_ERROR;
}