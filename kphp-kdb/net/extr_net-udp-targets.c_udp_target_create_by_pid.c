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
struct process_id {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 struct udp_target* __udp_target_create (struct process_id*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_4in6 (unsigned char*,int /*<<< orphan*/ ) ; 

struct udp_target *udp_target_create_by_pid (struct process_id *PID, int *was_created) {
  static unsigned char ipv6[16];
  set_4in6 (ipv6, htonl (PID->ip));  
  return __udp_target_create (PID, 0, ipv6, PID->port, was_created);
}