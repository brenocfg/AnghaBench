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
struct receive_arg {int /*<<< orphan*/  cksum; scalar_t__ byteswap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fletcher_4_incremental_byteswap (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fletcher_4_incremental_native (void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
receive_cksum(struct receive_arg *ra, int len, void *buf)
{
	if (ra->byteswap) {
		(void) fletcher_4_incremental_byteswap(buf, len, &ra->cksum);
	} else {
		(void) fletcher_4_incremental_native(buf, len, &ra->cksum);
	}
}