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
typedef  scalar_t__ u32 ;
struct memcons {int /*<<< orphan*/  obuf_size; int /*<<< orphan*/  ibuf_size; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

u32 memcons_get_size(struct memcons *mc)
{
	return be32_to_cpu(mc->ibuf_size) + be32_to_cpu(mc->obuf_size);
}