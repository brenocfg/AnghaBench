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
struct nvme_ns_list {int /*<<< orphan*/ * ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void	nvme_ns_list_swapbytes(struct nvme_ns_list *s)
{
	int i;

	for (i = 0; i < 1024; i++)
		s->ns[i] = le32toh(s->ns[i]);
}