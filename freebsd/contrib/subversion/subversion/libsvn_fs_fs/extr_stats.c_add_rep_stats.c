#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int references; int expanded_size; int /*<<< orphan*/  chain_len; int /*<<< orphan*/  shared; int /*<<< orphan*/  uniques; int /*<<< orphan*/  total; } ;
typedef  TYPE_1__ svn_fs_fs__representation_stats_t ;
struct TYPE_7__ {int ref_count; int expanded_size; scalar_t__ chain_length; } ;
typedef  TYPE_2__ rep_stats_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_rep_pack_stats (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
add_rep_stats(svn_fs_fs__representation_stats_t *stats,
              rep_stats_t *rep)
{
  add_rep_pack_stats(&stats->total, rep);
  if (rep->ref_count == 1)
    add_rep_pack_stats(&stats->uniques, rep);
  else
    add_rep_pack_stats(&stats->shared, rep);

  stats->references += rep->ref_count;
  stats->expanded_size += rep->ref_count * rep->expanded_size;
  stats->chain_len += rep->chain_length;
}