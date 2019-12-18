#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_version_t ;
struct TYPE_2__ {int /*<<< orphan*/  const* (* get_version ) () ;} ;

/* Variables and functions */
 TYPE_1__ VTBL ; 
 int /*<<< orphan*/  const* stub1 () ; 

__attribute__((used)) static const svn_version_t *compat_get_version(void)
{
  return VTBL.get_version();
}