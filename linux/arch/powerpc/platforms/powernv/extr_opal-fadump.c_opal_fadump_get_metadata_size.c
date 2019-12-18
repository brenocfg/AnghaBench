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
typedef  int /*<<< orphan*/  u64 ;
struct opal_fadump_mem_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 

__attribute__((used)) static u64 opal_fadump_get_metadata_size(void)
{
	return PAGE_ALIGN(sizeof(struct opal_fadump_mem_struct));
}