#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* changes; int /*<<< orphan*/ * builder; } ;
typedef  TYPE_2__ svn_fs_x__changes_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_4__ {int nelts; } ;

/* Variables and functions */
 scalar_t__ svn_fs_x__string_table_builder_estimate_size (int /*<<< orphan*/ *) ; 

apr_size_t
svn_fs_x__changes_estimate_size(const svn_fs_x__changes_t *changes)
{
  /* CHANGES must be in 'builder' mode */
  if (changes->builder == NULL)
    return 0;

  /* string table code makes its own prediction,
   * changes should be < 10 bytes each,
   * some static overhead should be assumed */
  return svn_fs_x__string_table_builder_estimate_size(changes->builder)
       + changes->changes->nelts * 10
       + 100;
}