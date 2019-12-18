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
typedef  int /*<<< orphan*/  Skein_512_Ctxt_t ;

/* Variables and functions */
 int /*<<< orphan*/  Skein_512_Update (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static int
skein_incremental(void *buf, size_t size, void *arg)
{
	Skein_512_Ctxt_t *ctx = arg;
	(void) Skein_512_Update(ctx, buf, size);
	return (0);
}