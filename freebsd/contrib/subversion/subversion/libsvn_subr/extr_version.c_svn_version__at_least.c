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
struct TYPE_3__ {int major; int minor; int patch; scalar_t__* tag; } ;
typedef  TYPE_1__ svn_version_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

svn_boolean_t
svn_version__at_least(const svn_version_t *version,
                      int major,
                      int minor,
                      int patch)
{
  /* Compare major versions. */
  if (version->major < major)
    return FALSE;
  if (version->major > major)
    return TRUE;

  /* Major versions are the same.  Compare minor versions. */
  if (version->minor < minor)
    return FALSE;
  if (version->minor > minor)
    return TRUE;

  /* Major and minor versions are the same.  Compare patch
     versions. */
  if (version->patch < patch)
    return FALSE;
  if (version->patch > patch)
    return TRUE;

  /* Major, minor, and patch versions are identical matches.  But tags
     in our schema are always used for versions not yet quite at the
     given patch level. */
  if (version->tag && version->tag[0])
    return FALSE;

  return TRUE;
}