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
struct intr_irqsrc {int isrc_flags; int /*<<< orphan*/ * isrc_count; } ;

/* Variables and functions */
 int INTR_ISRCF_PPI ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
isrc_increment_count(struct intr_irqsrc *isrc)
{

	if (isrc->isrc_flags & INTR_ISRCF_PPI)
		atomic_add_long(&isrc->isrc_count[0], 1);
	else
		isrc->isrc_count[0]++;
}