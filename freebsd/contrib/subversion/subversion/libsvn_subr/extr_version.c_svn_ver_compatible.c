#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* tag; scalar_t__ major; scalar_t__ minor; scalar_t__ patch; } ;
typedef  TYPE_1__ svn_version_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 int svn_ver_equal (TYPE_1__ const*,TYPE_1__ const*) ; 

svn_boolean_t svn_ver_compatible(const svn_version_t *my_version,
                                 const svn_version_t *lib_version)
{
  /* With normal development builds the matching rules are stricter
     that for release builds, to avoid inadvertantly using the wrong
     libraries.  For backward compatibility testing of development
     builds one can use --disable-full-version-match to cause a
     development build to use the release build rules.  This allows
     the libraries from the newer development build to be used by an
     older development build. */

#ifndef SVN_DISABLE_FULL_VERSION_MATCH
  if (lib_version->tag[0] != '\0')
    /* Development library; require exact match. */
    return svn_ver_equal(my_version, lib_version);
  else if (my_version->tag[0] != '\0')
    /* Development client; must be newer than the library
       and have the same major and minor version. */
    return (my_version->major == lib_version->major
            && my_version->minor == lib_version->minor
            && my_version->patch > lib_version->patch);
#endif

  /* General compatibility rules for released versions. */
  return (my_version->major == lib_version->major
          && my_version->minor <= lib_version->minor);
}