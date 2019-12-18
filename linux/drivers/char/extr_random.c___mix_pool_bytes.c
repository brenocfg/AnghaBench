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
struct entropy_store {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  _mix_pool_bytes (struct entropy_store*,void const*,int) ; 
 int /*<<< orphan*/  trace_mix_pool_bytes_nolock (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mix_pool_bytes(struct entropy_store *r, const void *in,
			     int nbytes)
{
	trace_mix_pool_bytes_nolock(r->name, nbytes, _RET_IP_);
	_mix_pool_bytes(r, in, nbytes);
}