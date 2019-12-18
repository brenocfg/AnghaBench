#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ kind; int /*<<< orphan*/  mtime; int /*<<< orphan*/  filesize; int /*<<< orphan*/  special; } ;
typedef  TYPE_1__ svn_io_dirent2_t ;
struct TYPE_16__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int32_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_17__ {int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; scalar_t__ name; } ;
typedef  TYPE_3__ apr_finfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_ENOENT ; 
 int APR_FINFO_LINK ; 
 int APR_FINFO_MTIME ; 
 int APR_FINFO_NAME ; 
 int APR_FINFO_SIZE ; 
 int APR_FINFO_TYPE ; 
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ SVN__APR_STATUS_IS_ENOTDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* entry_name_to_utf8 (char const**,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_apr_finfo_to_node_kind (scalar_t__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 void* svn_io_dirent2_create (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_get_dirents3 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_stat (TYPE_3__*,char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 

svn_error_t *
svn_io_stat_dirent2(const svn_io_dirent2_t **dirent_p,
                    const char *path,
                    svn_boolean_t verify_truename,
                    svn_boolean_t ignore_enoent,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  apr_finfo_t finfo;
  svn_io_dirent2_t *dirent;
  svn_error_t *err;
  apr_int32_t wanted = APR_FINFO_TYPE | APR_FINFO_LINK
                       | APR_FINFO_SIZE | APR_FINFO_MTIME;

#if defined(WIN32) || defined(__OS2__)
  if (verify_truename)
    wanted |= APR_FINFO_NAME;
#endif

  err = svn_io_stat(&finfo, path, wanted, scratch_pool);

  if (err && ignore_enoent &&
      (APR_STATUS_IS_ENOENT(err->apr_err)
       || SVN__APR_STATUS_IS_ENOTDIR(err->apr_err)))
    {
      svn_error_clear(err);
      dirent = svn_io_dirent2_create(result_pool);
      SVN_ERR_ASSERT(dirent->kind == svn_node_none);

      *dirent_p = dirent;
      return SVN_NO_ERROR;
    }
  SVN_ERR(err);

#if defined(WIN32) || defined(__OS2__) || defined(DARWIN)
  if (verify_truename)
    {
      const char *requested_name = svn_dirent_basename(path, NULL);

      if (requested_name[0] == '\0')
        {
          /* No parent directory. No need to stat/verify */
        }
#if defined(WIN32) || defined(__OS2__)
      else if (finfo.name)
        {
          const char *name_on_disk;
          SVN_ERR(entry_name_to_utf8(&name_on_disk, finfo.name, path,
                                     scratch_pool));

          if (strcmp(name_on_disk, requested_name) /* != 0 */)
            {
              if (ignore_enoent)
                {
                  *dirent_p = svn_io_dirent2_create(result_pool);
                  return SVN_NO_ERROR;
                }
              else
                return svn_error_createf(APR_ENOENT, NULL,
                          _("Path '%s' not found, case obstructed by '%s'"),
                          svn_dirent_local_style(path, scratch_pool),
                          name_on_disk);
            }
        }
#elif defined(DARWIN)
      /* Currently apr doesn't set finfo.name on DARWIN, returning
                   APR_INCOMPLETE.
         ### Can we optimize this in another way? */
      else
        {
          apr_hash_t *dirents;

          err = svn_io_get_dirents3(&dirents,
                                    svn_dirent_dirname(path, scratch_pool),
                                    TRUE /* only_check_type */,
                                    scratch_pool, scratch_pool);

          if (err && ignore_enoent
              && (APR_STATUS_IS_ENOENT(err->apr_err)
                  || SVN__APR_STATUS_IS_ENOTDIR(err->apr_err)))
            {
              svn_error_clear(err);

              *dirent_p = svn_io_dirent2_create(result_pool);
              return SVN_NO_ERROR;
            }
          else
            SVN_ERR(err);

          if (! svn_hash_gets(dirents, requested_name))
            {
              if (ignore_enoent)
                {
                  *dirent_p = svn_io_dirent2_create(result_pool);
                  return SVN_NO_ERROR;
                }
              else
                return svn_error_createf(APR_ENOENT, NULL,
                          _("Path '%s' not found"),
                          svn_dirent_local_style(path, scratch_pool));
            }
        }
#endif
    }
#endif

  dirent = svn_io_dirent2_create(result_pool);
  map_apr_finfo_to_node_kind(&(dirent->kind), &(dirent->special), &finfo);

  dirent->filesize = finfo.size;
  dirent->mtime = finfo.mtime;

  *dirent_p = dirent;

  return SVN_NO_ERROR;
}