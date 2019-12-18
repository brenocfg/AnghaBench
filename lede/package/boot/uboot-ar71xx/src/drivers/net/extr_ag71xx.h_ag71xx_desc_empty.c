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
struct ag71xx_desc {int ctrl; } ;

/* Variables and functions */
 int DESC_EMPTY ; 

__attribute__((used)) static inline int ag71xx_desc_empty(struct ag71xx_desc *desc)
{
	return ((desc->ctrl & DESC_EMPTY) != 0);
}