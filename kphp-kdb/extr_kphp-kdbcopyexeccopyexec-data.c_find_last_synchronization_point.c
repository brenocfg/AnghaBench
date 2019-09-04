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
 int copyexec_aux_replay_binlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ last_decryption_failed_transaction_pos ; 
 int last_synchronization_point_id ; 
 scalar_t__ last_synchronization_point_pos ; 
 int /*<<< orphan*/  replay_synchronization_point ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int find_last_synchronization_point (void) {
  last_synchronization_point_id = 0;
  last_decryption_failed_transaction_pos = last_synchronization_point_pos = 0;
  int r = copyexec_aux_replay_binlog (0, replay_synchronization_point);
  if (r < 0) {
    vkprintf (1, "find_last_synchronization_point: copyexec_aux_replay_binlog returns %d.\n", r);
  }
  if (last_decryption_failed_transaction_pos > last_synchronization_point_pos) {
    kprintf ("Couldn't decrypt transaction at %lld pos, last synchronization point pos is %lld.\n", last_decryption_failed_transaction_pos, last_synchronization_point_pos);
    exit (1);
  }
  return last_synchronization_point_id;
}