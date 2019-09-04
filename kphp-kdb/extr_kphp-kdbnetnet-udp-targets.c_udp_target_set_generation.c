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
struct udp_target {int generation; int /*<<< orphan*/  PID; } ;

/* Variables and functions */
 int /*<<< orphan*/  udp_target_renew (struct udp_target*,int /*<<< orphan*/ *,int) ; 

void udp_target_set_generation (struct udp_target *S, int generation) {
  if (S->generation >= generation) { return; }
  udp_target_renew (S, &S->PID, generation);
}