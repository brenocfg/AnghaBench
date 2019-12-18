#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct nvme_resv_status {int* regctl; TYPE_1__* ctrlr; int /*<<< orphan*/  gen; } ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_2__ {void* rkey; void* hostid; int /*<<< orphan*/  ctrlr_id; } ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 void* le64toh (void*) ; 

__attribute__((used)) static inline
void	nvme_resv_status_swapbytes(struct nvme_resv_status *s, size_t size)
{
	u_int i, n;

	s->gen = le32toh(s->gen);
	n = (s->regctl[1] << 8) | s->regctl[0];
	n = MIN(n, (size - sizeof(s)) / sizeof(s->ctrlr[0]));
	for (i = 0; i < n; i++) {
		s->ctrlr[i].ctrlr_id = le16toh(s->ctrlr[i].ctrlr_id);
		s->ctrlr[i].hostid = le64toh(s->ctrlr[i].hostid);
		s->ctrlr[i].rkey = le64toh(s->ctrlr[i].rkey);
	}
}