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
struct evrpc_base {int dummy; } ;

/* Variables and functions */
 scalar_t__ EVRPC_UNREGISTER (struct evrpc_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Message ; 
 int /*<<< orphan*/  NeverReply ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  evrpc_free (struct evrpc_base*) ; 

__attribute__((used)) static void
rpc_teardown(struct evrpc_base *base)
{
	assert(EVRPC_UNREGISTER(base, Message) == 0);
	assert(EVRPC_UNREGISTER(base, NeverReply) == 0);

	evrpc_free(base);
}