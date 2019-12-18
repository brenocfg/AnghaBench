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
struct rpc_kicked {int dummy; } ;
struct rpc_delays {int /*<<< orphan*/  medium_delay; int /*<<< orphan*/  slow_delay; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  delays_received; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIUM_REQUEST_DELAY ; 
 int /*<<< orphan*/  SLOW_REQUEST_DELAY ; 
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int rpc_execute_delays (struct connection *c, struct rpc_delays *P, int len) {
  vkprintf (2, "rpc_delays: len = %d\n", len);

  if (len != sizeof (struct rpc_kicked)) {
    return 0;
  }
  STATS->structured.delays_received ++;
  SLOW_REQUEST_DELAY = P->slow_delay;
  MEDIUM_REQUEST_DELAY = P->medium_delay;
  return 0;
}