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
union drbd_dev_state {scalar_t__ conn; } ;

/* Variables and functions */
 scalar_t__ C_AHEAD ; 
 scalar_t__ C_WF_BITMAP_S ; 

__attribute__((used)) static bool drbd_should_send_out_of_sync(union drbd_dev_state s)
{
	return s.conn == C_AHEAD || s.conn == C_WF_BITMAP_S;
	/* pdsk = D_INCONSISTENT as a consequence. Protocol 96 check not necessary
	   since we enter state C_AHEAD only if proto >= 96 */
}