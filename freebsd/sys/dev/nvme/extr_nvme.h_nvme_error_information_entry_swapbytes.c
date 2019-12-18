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
struct nvme_error_information_entry {void* ttsi; void* csi; int /*<<< orphan*/  nsid; void* lba; void* error_location; void* status; void* cid; void* sqid; void* error_count; } ;

/* Variables and functions */
 void* le16toh (void*) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 void* le64toh (void*) ; 

__attribute__((used)) static inline
void	nvme_error_information_entry_swapbytes(struct nvme_error_information_entry *s)
{

	s->error_count = le64toh(s->error_count);
	s->sqid = le16toh(s->sqid);
	s->cid = le16toh(s->cid);
	s->status = le16toh(s->status);
	s->error_location = le16toh(s->error_location);
	s->lba = le64toh(s->lba);
	s->nsid = le32toh(s->nsid);
	s->csi = le64toh(s->csi);
	s->ttsi = le16toh(s->ttsi);
}