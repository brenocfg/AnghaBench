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
struct nvme_qpair {int id; int phase; int num_entries; struct nvme_command* cmd; struct nvme_completion* cpl; } ;
struct nvme_completion {int dummy; } ;
struct nvme_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_dump_command (struct nvme_command*) ; 
 int /*<<< orphan*/  nvme_dump_completion (struct nvme_completion*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
nvme_dump_queue(struct nvme_qpair *qpair)
{
	struct nvme_completion *cpl;
	struct nvme_command *cmd;
	int i;

	printf("id:%04Xh phase:%d\n", qpair->id, qpair->phase);

	printf("Completion queue:\n");
	for (i = 0; i < qpair->num_entries; i++) {
		cpl = &qpair->cpl[i];
		printf("%05d: ", i);
		nvme_dump_completion(cpl);
	}

	printf("Submission queue:\n");
	for (i = 0; i < qpair->num_entries; i++) {
		cmd = &qpair->cmd[i];
		printf("%05d: ", i);
		nvme_dump_command(cmd);
	}
}