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
 int /*<<< orphan*/  init_amortization_tables () ; 
 int /*<<< orphan*/  replay_logevent ; 
 int /*<<< orphan*/  weights_hash_init () ; 
 int /*<<< orphan*/  weights_replay_logevent ; 

int init_weights_data (int schema) {
  replay_logevent = weights_replay_logevent;
  init_amortization_tables ();
  weights_hash_init ();
  return 0;
}