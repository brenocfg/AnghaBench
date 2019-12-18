#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  php_immediate_stats_t ;

/* Variables and functions */
 int QSIZE ; 
 int RPC_PHP_IMMEDIATE_STATS ; 
 int /*<<< orphan*/  dl_passert (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_pstr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  immediate_stats ; 
 int master_pipe_fast_write ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pipe_fast_packet_id ; 
 int /*<<< orphan*/  prepare_rpc_query_raw (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ write (int,int*,size_t) ; 

void write_immediate_stats_to_pipe() {
  if (master_pipe_fast_write != -1) {
#define QSIZE (sizeof (php_immediate_stats_t) + 1 + sizeof (int) * 5 + 3) & -4
    int q[QSIZE];
    int qsize = QSIZE;
#undef QSIZE
    memset (q, 0, (size_t)qsize);

    q[2] = RPC_PHP_IMMEDIATE_STATS;
    memcpy (q + 3, &immediate_stats, sizeof (php_immediate_stats_t));

    prepare_rpc_query_raw (pipe_fast_packet_id++, q, qsize);
    int err = (int)write (master_pipe_fast_write, q, (size_t)qsize);
    dl_passert (err == qsize, dl_pstr ("error [%d] during write to pipe", errno));
  }
}