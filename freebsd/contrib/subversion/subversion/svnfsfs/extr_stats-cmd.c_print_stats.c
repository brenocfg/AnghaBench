#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ count; scalar_t__ packed_size; } ;
struct TYPE_16__ {TYPE_3__ total; } ;
struct TYPE_20__ {scalar_t__ overhead_size; scalar_t__ count; scalar_t__ packed_size; scalar_t__ expanded_size; } ;
struct TYPE_21__ {double chain_len; TYPE_4__ total; scalar_t__ expanded_size; } ;
struct TYPE_17__ {scalar_t__ count; scalar_t__ sum; } ;
struct TYPE_18__ {TYPE_1__ total; } ;
struct TYPE_23__ {scalar_t__ count; scalar_t__ size; } ;
struct TYPE_22__ {scalar_t__ count; scalar_t__ size; } ;
struct TYPE_24__ {scalar_t__ count; scalar_t__ size; } ;
struct TYPE_25__ {int /*<<< orphan*/  dir_prop_rep_histogram; int /*<<< orphan*/  dir_prop_histogram; int /*<<< orphan*/  dir_rep_histogram; int /*<<< orphan*/  dir_histogram; int /*<<< orphan*/  file_prop_rep_histogram; int /*<<< orphan*/  file_prop_histogram; int /*<<< orphan*/  file_rep_histogram; int /*<<< orphan*/  file_histogram; int /*<<< orphan*/  rep_size_histogram; int /*<<< orphan*/  node_size_histogram; int /*<<< orphan*/  largest_changes; TYPE_11__ file_prop_rep_stats; TYPE_11__ dir_prop_rep_stats; TYPE_11__ file_rep_stats; TYPE_11__ dir_rep_stats; TYPE_5__ total_rep_stats; TYPE_2__ added_rep_size_histogram; TYPE_7__ file_node_stats; TYPE_6__ dir_node_stats; TYPE_8__ total_node_stats; scalar_t__ change_count; scalar_t__ change_len; scalar_t__ revision_count; scalar_t__ total_size; } ;
typedef  TYPE_9__ svn_fs_fs__stats_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  print_extensions_by_changes (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_extensions_by_nodes (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_extensions_by_reps (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_histogram (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_histograms_by_extension (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_largest_reps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_rep_stats (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* svn__ui64toa_sep (scalar_t__,char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_stats(svn_fs_fs__stats_t *stats,
            apr_pool_t *pool)
{
  /* print results */
  printf("\n\nGlobal statistics:\n");
  printf(_("%20s bytes in %12s revisions\n"
           "%20s bytes in %12s changes\n"
           "%20s bytes in %12s node revision records\n"
           "%20s bytes in %12s representations\n"
           "%20s bytes expanded representation size\n"
           "%20s bytes with rep-sharing off\n"),
         svn__ui64toa_sep(stats->total_size, ',', pool),
         svn__ui64toa_sep(stats->revision_count, ',', pool),
         svn__ui64toa_sep(stats->change_len, ',', pool),
         svn__ui64toa_sep(stats->change_count, ',', pool),
         svn__ui64toa_sep(stats->total_node_stats.size, ',', pool),
         svn__ui64toa_sep(stats->total_node_stats.count, ',', pool),
         svn__ui64toa_sep(stats->total_rep_stats.total.packed_size, ',',
                         pool),
         svn__ui64toa_sep(stats->total_rep_stats.total.count, ',', pool),
         svn__ui64toa_sep(stats->total_rep_stats.total.expanded_size, ',',
                         pool),
         svn__ui64toa_sep(stats->total_rep_stats.expanded_size, ',', pool));

  printf("\nNoderev statistics:\n");
  printf(_("%20s bytes in %12s nodes total\n"
           "%20s bytes in %12s directory noderevs\n"
           "%20s bytes in %12s file noderevs\n"),
         svn__ui64toa_sep(stats->total_node_stats.size, ',', pool),
         svn__ui64toa_sep(stats->total_node_stats.count, ',', pool),
         svn__ui64toa_sep(stats->dir_node_stats.size, ',', pool),
         svn__ui64toa_sep(stats->dir_node_stats.count, ',', pool),
         svn__ui64toa_sep(stats->file_node_stats.size, ',', pool),
         svn__ui64toa_sep(stats->file_node_stats.count, ',', pool));

  printf("\nRepresentation statistics:\n");
  printf(_("%20s bytes in %12s representations total\n"
           "%20s bytes in %12s directory representations\n"
           "%20s bytes in %12s file representations\n"
           "%20s bytes in %12s representations of added file nodes\n"
           "%20s bytes in %12s directory property representations\n"
           "%20s bytes in %12s file property representations\n"
           "                         with %12.3f average delta chain length\n"
           "%20s bytes in header & footer overhead\n"),
         svn__ui64toa_sep(stats->total_rep_stats.total.packed_size, ',',
                         pool),
         svn__ui64toa_sep(stats->total_rep_stats.total.count, ',', pool),
         svn__ui64toa_sep(stats->dir_rep_stats.total.packed_size, ',',
                         pool),
         svn__ui64toa_sep(stats->dir_rep_stats.total.count, ',', pool),
         svn__ui64toa_sep(stats->file_rep_stats.total.packed_size, ',',
                         pool),
         svn__ui64toa_sep(stats->file_rep_stats.total.count, ',', pool),
         svn__ui64toa_sep(stats->added_rep_size_histogram.total.sum, ',',
                         pool),
         svn__ui64toa_sep(stats->added_rep_size_histogram.total.count, ',',
                         pool),
         svn__ui64toa_sep(stats->dir_prop_rep_stats.total.packed_size, ',',
                         pool),
         svn__ui64toa_sep(stats->dir_prop_rep_stats.total.count, ',', pool),
         svn__ui64toa_sep(stats->file_prop_rep_stats.total.packed_size, ',',
                         pool),
         svn__ui64toa_sep(stats->file_prop_rep_stats.total.count, ',', pool),
         stats->total_rep_stats.chain_len
            / (double)stats->total_rep_stats.total.count,
         svn__ui64toa_sep(stats->total_rep_stats.total.overhead_size, ',',
                         pool));

  printf("\nDirectory representation statistics:\n");
  print_rep_stats(&stats->dir_rep_stats, pool);
  printf("\nFile representation statistics:\n");
  print_rep_stats(&stats->file_rep_stats, pool);
  printf("\nDirectory property representation statistics:\n");
  print_rep_stats(&stats->dir_prop_rep_stats, pool);
  printf("\nFile property representation statistics:\n");
  print_rep_stats(&stats->file_prop_rep_stats, pool);

  printf("\nLargest representations:\n");
  print_largest_reps(stats->largest_changes, pool);
  printf("\nExtensions by number of representations:\n");
  print_extensions_by_changes(stats, pool);
  printf("\nExtensions by size of changed files:\n");
  print_extensions_by_nodes(stats, pool);
  printf("\nExtensions by size of representations:\n");
  print_extensions_by_reps(stats, pool);

  printf("\nHistogram of expanded node sizes:\n");
  print_histogram(&stats->node_size_histogram, pool);
  printf("\nHistogram of representation sizes:\n");
  print_histogram(&stats->rep_size_histogram, pool);
  printf("\nHistogram of file sizes:\n");
  print_histogram(&stats->file_histogram, pool);
  printf("\nHistogram of file representation sizes:\n");
  print_histogram(&stats->file_rep_histogram, pool);
  printf("\nHistogram of file property sizes:\n");
  print_histogram(&stats->file_prop_histogram, pool);
  printf("\nHistogram of file property representation sizes:\n");
  print_histogram(&stats->file_prop_rep_histogram, pool);
  printf("\nHistogram of directory sizes:\n");
  print_histogram(&stats->dir_histogram, pool);
  printf("\nHistogram of directory representation sizes:\n");
  print_histogram(&stats->dir_rep_histogram, pool);
  printf("\nHistogram of directory property sizes:\n");
  print_histogram(&stats->dir_prop_histogram, pool);
  printf("\nHistogram of directory property representation sizes:\n");
  print_histogram(&stats->dir_prop_rep_histogram, pool);

  print_histograms_by_extension(stats, pool);
}