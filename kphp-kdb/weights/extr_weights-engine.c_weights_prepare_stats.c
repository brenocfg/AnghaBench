#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  avg; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ weights_half_life_stat_t ;
struct connection {int dummy; } ;
struct TYPE_8__ {int pos; } ;
typedef  TYPE_2__ stats_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  AM_GET_MEMORY_USAGE_SELF ; 
 int /*<<< orphan*/  FullVersionStr ; 
 int /*<<< orphan*/  SB_BINLOG ; 
 int /*<<< orphan*/  SB_INDEX ; 
 int /*<<< orphan*/  SB_PRINT_I32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_QUERIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  at_queries ; 
 int /*<<< orphan*/  get_vector_queries ; 
 int /*<<< orphan*/  incr_queries ; 
 int /*<<< orphan*/  sb_memory (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_prepare (TYPE_2__*,struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_printf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_half_life_queries ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  tot_amortization_tables ; 
 int /*<<< orphan*/  tot_counters_arrays ; 
 int /*<<< orphan*/  tot_subscriptions ; 
 int /*<<< orphan*/  tot_vectors ; 
 int /*<<< orphan*/  vector_hash_prime ; 
 int /*<<< orphan*/  weights_half_life_stats (TYPE_1__*) ; 

int weights_prepare_stats (struct connection *c) {
  stats_buffer_t sb;
  sb_prepare (&sb, c, stats_buff, STATS_BUFF_SIZE);
  sb_memory (&sb, AM_GET_MEMORY_USAGE_SELF);
  SB_BINLOG;
  SB_INDEX;

  SB_PRINT_QUERIES(incr_queries);
  SB_PRINT_QUERIES(set_half_life_queries);
  SB_PRINT_QUERIES(at_queries);
  SB_PRINT_QUERIES(get_vector_queries);

  SB_PRINT_I32(tot_vectors);
  SB_PRINT_I32(tot_amortization_tables);
  SB_PRINT_I32(tot_counters_arrays);
  SB_PRINT_I32(tot_subscriptions);
  SB_PRINT_I32(vector_hash_prime);

  weights_half_life_stat_t half_life;
  weights_half_life_stats (&half_life);
  SB_PRINT_I32(half_life.min);
  SB_PRINT_I32(half_life.max);
  sb_printf (&sb, "half_life.avg\t%.3lf\n", half_life.avg);

  sb_printf (&sb, "version\t%s\n", FullVersionStr);

  return sb.pos;
}