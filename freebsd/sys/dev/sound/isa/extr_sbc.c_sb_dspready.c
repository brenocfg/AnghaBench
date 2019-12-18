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
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBDSP_STATUS ; 
 int sb_rd (struct resource*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sb_dspready(struct resource *io)
{
	return ((sb_rd(io, SBDSP_STATUS) & 0x80) == 0);
}