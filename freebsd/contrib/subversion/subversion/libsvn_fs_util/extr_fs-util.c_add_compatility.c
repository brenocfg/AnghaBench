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
struct TYPE_3__ {int major; int minor; } ;
typedef  TYPE_1__ svn_version_t ;

/* Variables and functions */

__attribute__((used)) static void
add_compatility(svn_version_t *version,
                int compat_major,
                int compat_minor)
{
  if (   version->major > compat_major
      || (version->major == compat_major && version->minor > compat_minor))
    {
      version->major = compat_major;
      version->minor = compat_minor;
    }
}