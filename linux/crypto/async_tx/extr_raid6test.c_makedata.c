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
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * data ; 
 int /*<<< orphan*/ * dataptrs ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prandom_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void makedata(int disks)
{
	int i;

	for (i = 0; i < disks; i++) {
		prandom_bytes(page_address(data[i]), PAGE_SIZE);
		dataptrs[i] = data[i];
	}
}