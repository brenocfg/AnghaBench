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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 char* debian_release (int /*<<< orphan*/ *) ; 
 char* lsb_release (int /*<<< orphan*/ *) ; 
 char* redhat_release (int /*<<< orphan*/ *) ; 
 char* release_name_from_uname (int /*<<< orphan*/ *) ; 
 char* suse_release (int /*<<< orphan*/ *) ; 
 char* systemd_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
linux_release_name(apr_pool_t *pool)
{
  const char *uname_release = release_name_from_uname(pool);

  /* Try anything that has /usr/bin/lsb_release.
     Covers, for example, Debian, Ubuntu and SuSE.  */
  const char *release_name = lsb_release(pool);

  /* Try the systemd way (covers Arch). */
  if (!release_name)
    release_name = systemd_release(pool);

  /* Try RHEL/Fedora/CentOS */
  if (!release_name)
    release_name = redhat_release(pool);

  /* Try Non-LSB SuSE */
  if (!release_name)
    release_name = suse_release(pool);

  /* Try non-LSB Debian */
  if (!release_name)
    release_name = debian_release(pool);

  if (!release_name)
    return uname_release;

  if (!uname_release)
    return release_name;

  return apr_psprintf(pool, "%s [%s]", release_name, uname_release);
}