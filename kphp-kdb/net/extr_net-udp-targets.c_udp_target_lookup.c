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
struct udp_target {int dummy; } ;
struct process_id {int dummy; } ;

/* Variables and functions */
 struct udp_target* udp_target_get_by_pid (struct process_id*) ; 

struct udp_target *udp_target_lookup (struct process_id *PID) {
  return udp_target_get_by_pid (PID);
}