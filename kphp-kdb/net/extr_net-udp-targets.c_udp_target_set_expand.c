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
struct udp_target_set {int state; struct udp_target* S; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  generation; int /*<<< orphan*/  utime; int /*<<< orphan*/  pid; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct udp_target {struct udp_target_set* ST; } ;
struct process_id {int /*<<< orphan*/  utime; int /*<<< orphan*/  pid; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct udp_target* udp_target_alloc (struct process_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void udp_target_set_expand (struct udp_target_set *ST) {
  assert (ST && ST->state == 1);
  struct process_id P;
  P.ip = ST->ip;
  P.port = ST->port;
  P.pid = ST->pid;
  P.utime = ST->utime;

  struct udp_target *S = udp_target_alloc (&P, ST->generation, ST->dst_ipv6, ST->dst_port);
  
  ST->state = 2;
  ST->S = S;
  S->ST = ST;
}