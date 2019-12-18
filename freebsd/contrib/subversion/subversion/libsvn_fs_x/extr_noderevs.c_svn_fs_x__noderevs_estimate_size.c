#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* reps; TYPE_2__* ids; TYPE_1__* noderevs; int /*<<< orphan*/ * builder; } ;
typedef  TYPE_4__ svn_fs_x__noderevs_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_8__ {int nelts; } ;
struct TYPE_7__ {int nelts; } ;
struct TYPE_6__ {int nelts; } ;

/* Variables and functions */
 scalar_t__ svn_fs_x__string_table_builder_estimate_size (int /*<<< orphan*/ *) ; 

apr_size_t
svn_fs_x__noderevs_estimate_size(const svn_fs_x__noderevs_t *container)
{
  /* CONTAINER must be in 'builder' mode */
  if (container->builder == NULL)
    return 0;

  /* string table code makes its own prediction,
   * noderevs should be < 16 bytes each,
   * id parts < 4 bytes each,
   * data representations < 40 bytes each,
   * property representations < 30 bytes each,
   * some static overhead should be assumed */
  return svn_fs_x__string_table_builder_estimate_size(container->builder)
       + container->noderevs->nelts * 16
       + container->ids->nelts * 4
       + container->reps->nelts * 40
       + 100;
}