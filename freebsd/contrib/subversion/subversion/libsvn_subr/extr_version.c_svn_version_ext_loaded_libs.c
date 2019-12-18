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
struct TYPE_3__ {int /*<<< orphan*/  const* loaded_libs; } ;
typedef  TYPE_1__ svn_version_extended_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */

const apr_array_header_t *
svn_version_ext_loaded_libs(const svn_version_extended_t *ext_info)
{
  return ext_info->loaded_libs;
}