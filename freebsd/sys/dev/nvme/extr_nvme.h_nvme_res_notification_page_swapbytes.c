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
struct nvme_res_notification_page {int /*<<< orphan*/  nsid; int /*<<< orphan*/  log_page_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void	nvme_res_notification_page_swapbytes(struct nvme_res_notification_page *s)
{
	s->log_page_count = le64toh(s->log_page_count);
	s->nsid = le32toh(s->nsid);
}