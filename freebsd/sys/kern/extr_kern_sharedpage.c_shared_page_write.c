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

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void const*,scalar_t__,int) ; 
 scalar_t__ shared_page_mapping ; 

void
shared_page_write(int base, int size, const void *data)
{

	bcopy(data, shared_page_mapping + base, size);
}