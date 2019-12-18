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
struct nvme_firmware_page {int /*<<< orphan*/ * revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void	nvme_firmware_page_swapbytes(struct nvme_firmware_page *s)
{
	int i;

	for (i = 0; i < 7; i++)
		s->revision[i] = le64toh(s->revision[i]);
}