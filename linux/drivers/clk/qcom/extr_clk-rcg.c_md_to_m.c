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
typedef  int u32 ;
struct mn {int m_val_shift; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 md_to_m(struct mn *mn, u32 md)
{
	md >>= mn->m_val_shift;
	md &= BIT(mn->width) - 1;
	return md;
}