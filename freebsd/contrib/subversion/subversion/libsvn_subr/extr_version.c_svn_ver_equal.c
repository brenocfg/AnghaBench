#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ major; scalar_t__ minor; scalar_t__ patch; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ svn_version_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_boolean_t svn_ver_equal(const svn_version_t *my_version,
                            const svn_version_t *lib_version)
{
  return (my_version->major == lib_version->major
          && my_version->minor == lib_version->minor
          && my_version->patch == lib_version->patch
          && 0 == strcmp(my_version->tag, lib_version->tag));
}