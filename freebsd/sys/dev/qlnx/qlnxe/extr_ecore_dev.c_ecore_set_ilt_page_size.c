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
typedef  int /*<<< orphan*/  u8 ;
struct ecore_dev {int /*<<< orphan*/  ilt_page_size; } ;

/* Variables and functions */

void ecore_set_ilt_page_size(struct ecore_dev *p_dev, u8 ilt_page_size)
{
	p_dev->ilt_page_size = ilt_page_size;
}