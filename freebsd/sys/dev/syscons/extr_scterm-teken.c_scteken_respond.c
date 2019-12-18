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
typedef  int /*<<< orphan*/  scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  sc_respond (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scteken_respond(void *arg, const void *buf, size_t len)
{
	scr_stat *scp = arg;

	sc_respond(scp, buf, len, 0);
}