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
struct TYPE_2__ {int /*<<< orphan*/  scratch_buffer; } ;
struct worker {TYPE_1__ env; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  load_msg_cache (int /*<<< orphan*/ *,struct worker*) ; 
 int /*<<< orphan*/  load_rrset_cache (int /*<<< orphan*/ *,struct worker*) ; 
 int read_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
load_cache(RES* ssl, struct worker* worker)
{
	if(!load_rrset_cache(ssl, worker))
		return 0;
	if(!load_msg_cache(ssl, worker))
		return 0;
	return read_fixed(ssl, worker->env.scratch_buffer, "EOF");
}