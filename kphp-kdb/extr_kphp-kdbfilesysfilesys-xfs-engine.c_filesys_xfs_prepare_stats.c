#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_5__ {int pos; } ;
typedef  TYPE_1__ stats_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  AM_GET_MEMORY_USAGE_SELF ; 
 int /*<<< orphan*/  FullVersionStr ; 
 int /*<<< orphan*/  SB_BINLOG ; 
 int /*<<< orphan*/  SB_INDEX ; 
 int /*<<< orphan*/  STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  compression_level ; 
 int /*<<< orphan*/  last_closed_transaction_id ; 
 int /*<<< orphan*/  last_closed_transaction_time ; 
 int /*<<< orphan*/  sb_memory (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_prepare (TYPE_1__*,struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_transaction_id ; 
 int /*<<< orphan*/  stats_buffer ; 
 int /*<<< orphan*/  transaction_id ; 
 int /*<<< orphan*/  volume_id ; 
 int /*<<< orphan*/  work_dir ; 

int filesys_xfs_prepare_stats (struct connection *c) {
  stats_buffer_t sb;
  sb_prepare (&sb, c, stats_buffer, STATS_BUFF_SIZE);  
  sb_memory (&sb, AM_GET_MEMORY_USAGE_SELF);
  SB_BINLOG;
  SB_INDEX;

  sb_printf (&sb,
      "volume_id\t%lld\n"
      "work_dir\t%s\n"
      "snapshot_compression_level\t%d\n"
      "start_transaction_id\t%d\n"
      "transaction_id\t%d\n"
      "last_closed_transaction_id\t%d\n"
      "last_closed_transaction_time\t%d\n"
      "version\t%s\n",
    volume_id,
    work_dir,
    compression_level,
    start_transaction_id,
    transaction_id,
    last_closed_transaction_id,
    last_closed_transaction_time,
    FullVersionStr
  );
  return sb.pos;
}