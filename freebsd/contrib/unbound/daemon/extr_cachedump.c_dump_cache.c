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
struct worker {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  dump_msg_cache (int /*<<< orphan*/ *,struct worker*) ; 
 int /*<<< orphan*/  dump_rrset_cache (int /*<<< orphan*/ *,struct worker*) ; 
 int ssl_printf (int /*<<< orphan*/ *,char*) ; 

int
dump_cache(RES* ssl, struct worker* worker)
{
	if(!dump_rrset_cache(ssl, worker))
		return 0;
	if(!dump_msg_cache(ssl, worker))
		return 0;
	return ssl_printf(ssl, "EOF\n");
}