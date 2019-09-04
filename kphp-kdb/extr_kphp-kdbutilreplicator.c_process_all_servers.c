#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct repl_server_status {scalar_t__ conn_generation; int flags; TYPE_1__* conn; struct repl_server_status* server_next; } ;
struct repl_client_status {scalar_t__ conn_generation; TYPE_2__* conn; } ;
struct related_binlog {int flags; int targets; struct repl_client_status** client; struct repl_server_status* server_first; } ;
struct TYPE_4__ {scalar_t__ generation; } ;
struct TYPE_3__ {scalar_t__ generation; } ;

/* Variables and functions */
 struct related_binlog* LR ; 
 int LRF_BROKEN ; 
 int LRF_CHANGED_TIME ; 
 int LRF_MASTER ; 
 int RS_ALLREAD ; 
 int RS_ALLSENT ; 
 int RS_FATAL ; 
 int /*<<< orphan*/  check_flush_client (struct repl_client_status*) ; 
 int /*<<< orphan*/  destroy_client (struct repl_client_status*) ; 
 int /*<<< orphan*/  destroy_server (struct repl_server_status*) ; 
 int local_rbs ; 
 int /*<<< orphan*/  process_server (struct repl_server_status*) ; 
 int /*<<< orphan*/  process_server_rotate (struct repl_server_status*) ; 
 int /*<<< orphan*/  process_server_time (struct repl_server_status*) ; 
 scalar_t__ servers_readall ; 
 scalar_t__ servers_sentall ; 

int process_all_servers (void) {
  int i;
  servers_readall = servers_sentall = 0;
  for (i = 0; i < local_rbs; i++) {
    struct related_binlog *R = &LR[i];
    if ((R->flags & (LRF_MASTER | LRF_BROKEN)) == LRF_MASTER) {
      struct repl_server_status *S, *NS;
      for (S = R->server_first; S != (struct repl_server_status *) R; S = NS) {
        NS = S->server_next;
        if (S->conn->generation != S->conn_generation || (S->flags & RS_FATAL) != 0) {
          destroy_server (S);
          continue;
        }

        process_server (S);
        process_server_rotate (S);
	if (R->flags & LRF_CHANGED_TIME) {
	  process_server_time (S);
	}

        if (S->flags & RS_ALLREAD) {
          servers_readall++;
        }
        if (S->flags & RS_ALLSENT) {
          servers_sentall++;
        }
      }
      R->flags &= ~LRF_CHANGED_TIME;
    }
    int j;
    for (j = 0; j < R->targets; j++) {
      if (R->client[j]) {
        struct repl_client_status *C = R->client[j];
        if (C->conn->generation != C->conn_generation) {
          destroy_client (C);
        } else {
          check_flush_client (C);
        }
      }
    }
  }
  return 0;
}