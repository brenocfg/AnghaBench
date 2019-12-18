#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int kind; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
 TYPE_1__* checksum_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  svn_checksum_fnv1a_32 131 
#define  svn_checksum_fnv1a_32x4 130 
#define  svn_checksum_md5 129 
#define  svn_checksum_sha1 128 

svn_checksum_t *
svn_checksum_dup(const svn_checksum_t *checksum,
                 apr_pool_t *pool)
{
  /* The duplicate of a NULL checksum is a NULL... */
  if (checksum == NULL)
    return NULL;

  /* Without this check on valid checksum kind a NULL svn_checksum_t
   * pointer is returned which could cause a core dump at an
   * indeterminate time in the future because callers are not
   * expecting a NULL pointer.  This commit forces an early abort() so
   * it's easier to track down where the issue arose. */
  switch (checksum->kind)
    {
      case svn_checksum_md5:
      case svn_checksum_sha1:
      case svn_checksum_fnv1a_32:
      case svn_checksum_fnv1a_32x4:
        return checksum_create(checksum->kind, checksum->digest, pool);

      default:
        SVN_ERR_MALFUNCTION_NO_RETURN();
        break;
    }
}