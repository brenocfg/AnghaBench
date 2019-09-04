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

/* Variables and functions */
 int RPC_PHP_FULL_STATS ; 
 int /*<<< orphan*/  dl_passert (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_pstr (char*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int* malloc (size_t) ; 
 int master_pipe_write ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pipe_packet_id ; 
 int /*<<< orphan*/  prepare_full_stats () ; 
 int /*<<< orphan*/  prepare_rpc_query_raw (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stats ; 
 int stats_len ; 
 scalar_t__ write (int,int*,size_t) ; 

void write_full_stats_to_pipe() {
  if (master_pipe_write != -1) {
    prepare_full_stats();

    int qsize = stats_len + 1 + (int)sizeof (int) * 5;
    qsize = (qsize + 3) & -4;
    int *q = malloc ((size_t)qsize);
    memset (q, 0, (size_t)qsize);

    q[2] = RPC_PHP_FULL_STATS;
    memcpy (q + 3, stats, (size_t)stats_len);

    prepare_rpc_query_raw (pipe_packet_id++, q, qsize);
    int err = (int)write (master_pipe_write, q, (size_t)qsize);
    dl_passert (err == qsize, dl_pstr ("error during write to pipe [%d]\n", master_pipe_write));
    if (err != qsize) {
      kill (getppid(), 9);
    }
    free (q);
  }
}