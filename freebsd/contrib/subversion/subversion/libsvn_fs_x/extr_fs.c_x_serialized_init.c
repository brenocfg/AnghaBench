#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  txn_list_lock; int /*<<< orphan*/  txn_current_lock; int /*<<< orphan*/  fs_pack_lock; int /*<<< orphan*/  fs_write_lock; int /*<<< orphan*/ * common_pool; } ;
typedef  TYPE_1__ svn_fs_x__shared_data_t ;
struct TYPE_8__ {TYPE_1__* shared; int /*<<< orphan*/  instance_id; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_9__ {int /*<<< orphan*/  uuid; TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FSX_SHARED_USERDATA_PREFIX ; 
 int /*<<< orphan*/  SVN_FS_X__USE_LOCK_MUTEX ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ apr_pool_userdata_get (void**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_pool_userdata_set (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_serialized_init(svn_fs_t *fs,
                  apr_pool_t *common_pool,
                  apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  const char *key;
  void *val;
  svn_fs_x__shared_data_t *ffsd;
  apr_status_t status;

  /* Note that we are allocating a small amount of long-lived data for
     each separate repository opened during the lifetime of the
     svn_fs_initialize pool.  It's unlikely that anyone will notice
     the modest expenditure; the alternative is to allocate each structure
     in a subpool, add a reference-count, and add a serialized destructor
     to the FS vtable.  That's more machinery than it's worth.

     Picking an appropriate key for the shared data is tricky, because,
     unfortunately, a filesystem UUID is not really unique.  It is implicitly
     shared between hotcopied (1), dump / loaded (2) or naively copied (3)
     filesystems.  We tackle this problem by using a combination of the UUID
     and an instance ID as the key.  This allows us to avoid key clashing
     in (1) and (2).

     Speaking of (3), there is not so much we can do about it, except maybe
     provide a convenient way of fixing things.  Naively copied filesystems
     have identical filesystem UUIDs *and* instance IDs.  With the key being
     a combination of these two, clashes can be fixed by changing either of
     them (or both), e.g. with svn_fs_set_uuid(). */


  SVN_ERR_ASSERT(fs->uuid);
  SVN_ERR_ASSERT(ffd->instance_id);

  key = apr_pstrcat(scratch_pool, SVN_FSX_SHARED_USERDATA_PREFIX,
                    fs->uuid, ":", ffd->instance_id, SVN_VA_NULL);
  status = apr_pool_userdata_get(&val, key, common_pool);
  if (status)
    return svn_error_wrap_apr(status, _("Can't fetch FSX shared data"));
  ffsd = val;

  if (!ffsd)
    {
      ffsd = apr_pcalloc(common_pool, sizeof(*ffsd));
      ffsd->common_pool = common_pool;

      /* POSIX fcntl locks are per-process, so we need a mutex for
         intra-process synchronization when grabbing the repository write
         lock. */
      SVN_ERR(svn_mutex__init(&ffsd->fs_write_lock,
                              SVN_FS_X__USE_LOCK_MUTEX, common_pool));

      /* ... the pack lock ... */
      SVN_ERR(svn_mutex__init(&ffsd->fs_pack_lock,
                              SVN_FS_X__USE_LOCK_MUTEX, common_pool));

      /* ... not to mention locking the txn-current file. */
      SVN_ERR(svn_mutex__init(&ffsd->txn_current_lock,
                              SVN_FS_X__USE_LOCK_MUTEX, common_pool));

      /* We also need a mutex for synchronizing access to the active
         transaction list and free transaction pointer. */
      SVN_ERR(svn_mutex__init(&ffsd->txn_list_lock, TRUE, common_pool));

      key = apr_pstrdup(common_pool, key);
      status = apr_pool_userdata_set(ffsd, key, NULL, common_pool);
      if (status)
        return svn_error_wrap_apr(status, _("Can't store FSX shared data"));
    }

  ffd->shared = ffsd;

  return SVN_NO_ERROR;
}