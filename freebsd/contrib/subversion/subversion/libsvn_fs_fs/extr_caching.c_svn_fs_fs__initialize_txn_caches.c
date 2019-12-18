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
struct TYPE_6__ {int /*<<< orphan*/  path; int /*<<< orphan*/  uuid; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ format; int /*<<< orphan*/ * txn_dir_cache; scalar_t__ concurrent_transactions; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  SVN_CACHE__MEMBUFFER_HIGH_PRIORITY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_TXN_CURRENT_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 scalar_t__ TRUE ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char const*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  create_cache (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_txn_callbacks (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get_global_membuffer_cache () ; 
 int /*<<< orphan*/  svn_fs_fs__deserialize_dir_entries ; 
 int /*<<< orphan*/  svn_fs_fs__serialize_txndir_entries ; 
 int /*<<< orphan*/  svn_uuid_generate (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__initialize_txn_caches(svn_fs_t *fs,
                                 const char *txn_id,
                                 apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  const char *prefix;

  /* We don't support caching for concurrent transactions in the SAME
   * FSFS session. Maybe, you forgot to clean POOL. */
  if (ffd->txn_dir_cache != NULL || ffd->concurrent_transactions)
    {
      ffd->txn_dir_cache = NULL;
      ffd->concurrent_transactions = TRUE;

      return SVN_NO_ERROR;
    }

  /* Transaction content needs to be carefully prefixed to virtually
     eliminate any chance for conflicts. The (repo, txn_id) pair
     should be unique but if the filesystem format doesn't store the
     global transaction ID via the txn-current file, and a transaction
     fails, it might be possible to start a new transaction later that
     receives the same id.  For such older formats, throw in an uuid as
     well -- just to be sure. */
  if (ffd->format >= SVN_FS_FS__MIN_TXN_CURRENT_FORMAT)
    prefix = apr_pstrcat(pool,
                         "fsfs:", fs->uuid,
                         "/", fs->path,
                         ":", txn_id,
                         ":", "TXNDIR",
                         SVN_VA_NULL);
  else
    prefix = apr_pstrcat(pool,
                         "fsfs:", fs->uuid,
                         "/", fs->path,
                         ":", txn_id,
                         ":", svn_uuid_generate(pool),
                         ":", "TXNDIR",
                         SVN_VA_NULL);

  /* create a txn-local directory cache */
  SVN_ERR(create_cache(&ffd->txn_dir_cache,
                       NULL,
                       svn_cache__get_global_membuffer_cache(),
                       1024, 8,
                       svn_fs_fs__serialize_txndir_entries,
                       svn_fs_fs__deserialize_dir_entries,
                       APR_HASH_KEY_STRING,
                       prefix,
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       TRUE, /* The TXN-ID is our namespace. */
                       fs,
                       TRUE,
                       pool, pool));

  /* reset the transaction-specific cache if the pool gets cleaned up. */
  init_txn_callbacks(fs, &(ffd->txn_dir_cache), pool);

  return SVN_NO_ERROR;
}