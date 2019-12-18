#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct fs_type_defn {struct fs_type_defn* next; int /*<<< orphan*/  fs_type; } ;
typedef  int /*<<< orphan*/  fs_library_vtable_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_UNKNOWN_FS_TYPE ; 
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  common_pool_lock ; 
 struct fs_type_defn* fs_modules ; 
 int /*<<< orphan*/ * get_library_vtable_direct (int /*<<< orphan*/ **,struct fs_type_defn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_or_allocate_third (struct fs_type_defn**,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_initialize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_library_vtable(fs_library_vtable_t **vtable, const char *fs_type,
                   apr_pool_t *pool)
{
  struct fs_type_defn **fst;
  svn_boolean_t known = FALSE;

  /* There are three FS module definitions known at compile time.  We
     want to check these without any locking overhead even when
     dynamic third party modules are enabled.  The third party modules
     cannot be checked until the lock is held.  */
  for (fst = &fs_modules; *fst; fst = &(*fst)->next)
    {
      if (strcmp(fs_type, (*fst)->fs_type) == 0)
        {
          known = TRUE;
          break;
        }
      else if (!(*fst)->next)
        {
          break;
        }
    }

#if defined(SVN_USE_DSO) && APR_HAS_DSO
  /* Third party FS modules that are unknown at compile time.

     A third party FS is identified by the file fs-type containing a
     third party name, say "foo".  The loader will load the DSO with
     the name "libsvn_fs_foo" and use the entry point with the name
     "svn_fs_foo__init".

     Note: the BDB and FSFS modules don't follow this naming scheme
     and this allows them to be used to test the third party loader.
     Change the content of fs-type to "base" in a BDB filesystem or to
     "fs" in an FSFS filesystem and they will be loaded as third party
     modules. */
  if (!known)
    {
      fst = &(*fst)->next;
      /* Best-effort init, see get_library_vtable_direct. */
      SVN_ERR(svn_fs_initialize(NULL));
      SVN_MUTEX__WITH_LOCK(common_pool_lock,
                           get_or_allocate_third(fst, fs_type));
      known = TRUE;
    }
#endif
  if (!known)
    return svn_error_createf(SVN_ERR_FS_UNKNOWN_FS_TYPE, NULL,
                             _("Unknown FS type '%s'"), fs_type);
  return get_library_vtable_direct(vtable, *fst, pool);
}