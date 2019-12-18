#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  overhead_size; int /*<<< orphan*/  expanded_size; int /*<<< orphan*/  packed_size; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ svn_fs_fs__rep_pack_stats_t ;
struct TYPE_6__ {scalar_t__ header_size; scalar_t__ expanded_size; scalar_t__ size; } ;
typedef  TYPE_2__ rep_stats_t ;

/* Variables and functions */

__attribute__((used)) static void
add_rep_pack_stats(svn_fs_fs__rep_pack_stats_t *stats,
                   rep_stats_t *rep)
{
  stats->count++;

  stats->packed_size += rep->size;
  stats->expanded_size += rep->expanded_size;
  stats->overhead_size += rep->header_size + 7 /* ENDREP\n */;
}