#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ip; } ;
struct rpc_target {TYPE_1__ PID; } ;

/* Variables and functions */
 struct rpc_target** Sarr ; 
 int SarrPos ; 
 int /*<<< orphan*/  assert (int) ; 

void __rpc_target_set_host (struct rpc_target *S) {
  if (!S->PID.ip) {
    assert (SarrPos < 10000);
    Sarr[SarrPos ++] = S;
  }
}