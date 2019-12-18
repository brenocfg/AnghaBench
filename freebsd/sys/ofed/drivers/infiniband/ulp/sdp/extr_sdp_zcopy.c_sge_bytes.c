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
struct ib_sge {scalar_t__ length; } ;

/* Variables and functions */

__attribute__((used)) static inline int sge_bytes(struct ib_sge *sge, int sge_cnt)
{
	int bytes = 0;

	while (sge_cnt > 0) {
		bytes += sge->length;
		sge++;
		sge_cnt--;
	}

	return bytes;
}