#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_7__* children; } ;
typedef  TYPE_8__ svn_skel_t ;
struct TYPE_24__ {int /*<<< orphan*/  expiration_date; int /*<<< orphan*/  creation_date; int /*<<< orphan*/  is_dav_comment; void* comment; void* owner; void* token; void* path; } ;
typedef  TYPE_9__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_22__ {TYPE_6__* next; } ;
struct TYPE_21__ {TYPE_5__* next; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {TYPE_4__* next; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {TYPE_3__* next; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {TYPE_10__* next; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {TYPE_1__* next; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_9__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  is_valid_lock_skel (TYPE_8__*) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 scalar_t__ svn_skel__matches_atom (TYPE_10__*,char*) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__parse_lock_skel(svn_lock_t **lock_p,
                             svn_skel_t *skel,
                             apr_pool_t *pool)
{
  svn_lock_t *lock;
  const char *timestr;

  /* Validate the skel. */
  if (! is_valid_lock_skel(skel))
    return skel_err("lock");

  /* Create the returned structure */
  lock = apr_pcalloc(pool, sizeof(*lock));

  /* PATH */
  lock->path = apr_pstrmemdup(pool, skel->children->next->data,
                              skel->children->next->len);

  /* LOCK-TOKEN */
  lock->token = apr_pstrmemdup(pool,
                               skel->children->next->next->data,
                               skel->children->next->next->len);

  /* OWNER */
  lock->owner = apr_pstrmemdup(pool,
                               skel->children->next->next->next->data,
                               skel->children->next->next->next->len);

  /* COMMENT  (could be just an empty atom) */
  if (skel->children->next->next->next->next->len)
    lock->comment =
      apr_pstrmemdup(pool,
                     skel->children->next->next->next->next->data,
                     skel->children->next->next->next->next->len);

  /* XML_P */
  if (svn_skel__matches_atom
      (skel->children->next->next->next->next->next, "1"))
    lock->is_dav_comment = TRUE;
  else
    lock->is_dav_comment = FALSE;

  /* CREATION-DATE */
  timestr = apr_pstrmemdup
    (pool,
     skel->children->next->next->next->next->next->next->data,
     skel->children->next->next->next->next->next->next->len);
  SVN_ERR(svn_time_from_cstring(&(lock->creation_date),
                                timestr, pool));

  /* EXPIRATION-DATE  (could be just an empty atom) */
  if (skel->children->next->next->next->next->next->next->next->len)
    {
      timestr =
        apr_pstrmemdup
        (pool,
         skel->children->next->next->next->next->next->next->next->data,
         skel->children->next->next->next->next->next->next->next->len);
      SVN_ERR(svn_time_from_cstring(&(lock->expiration_date),
                                    timestr, pool));
    }

  /* Return the structure. */
  *lock_p = lock;
  return SVN_NO_ERROR;
}