#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ count; scalar_t__ expanded_size; scalar_t__ packed_size; } ;
struct TYPE_5__ {scalar_t__ expanded_size; scalar_t__ count; scalar_t__ packed_size; } ;
struct TYPE_7__ {double chain_len; TYPE_2__ total; scalar_t__ references; scalar_t__ expanded_size; TYPE_1__ shared; } ;
typedef  TYPE_3__ svn_fs_fs__representation_stats_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 double MAX (double,double) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*,char*,double) ; 
 char* svn__ui64toa_sep (scalar_t__,char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_rep_stats(svn_fs_fs__representation_stats_t *stats,
                apr_pool_t *pool)
{
  printf(_("%20s bytes in %12s reps\n"
           "%20s bytes in %12s shared reps\n"
           "%20s bytes expanded size\n"
           "%20s bytes expanded shared size\n"
           "%20s bytes with rep-sharing off\n"
           "%20s shared references\n"
           "%20.3f average delta chain length\n"),
         svn__ui64toa_sep(stats->total.packed_size, ',', pool),
         svn__ui64toa_sep(stats->total.count, ',', pool),
         svn__ui64toa_sep(stats->shared.packed_size, ',', pool),
         svn__ui64toa_sep(stats->shared.count, ',', pool),
         svn__ui64toa_sep(stats->total.expanded_size, ',', pool),
         svn__ui64toa_sep(stats->shared.expanded_size, ',', pool),
         svn__ui64toa_sep(stats->expanded_size, ',', pool),
         svn__ui64toa_sep(stats->references - stats->total.count, ',', pool),
         stats->chain_len / MAX(1.0, (double)stats->total.count));
}