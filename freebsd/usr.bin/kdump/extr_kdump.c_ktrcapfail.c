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
struct ktr_cap_fail {int cap_type; int /*<<< orphan*/  cap_held; int /*<<< orphan*/  cap_needed; } ;

/* Variables and functions */
#define  CAPFAIL_INCREASE 131 
#define  CAPFAIL_LOOKUP 130 
#define  CAPFAIL_NOTCAPABLE 129 
#define  CAPFAIL_SYSCALL 128 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sysdecode_cap_rights (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ktrcapfail(struct ktr_cap_fail *ktr)
{
	switch (ktr->cap_type) {
	case CAPFAIL_NOTCAPABLE:
		/* operation on fd with insufficient capabilities */
		printf("operation requires ");
		sysdecode_cap_rights(stdout, &ktr->cap_needed);
		printf(", descriptor holds ");
		sysdecode_cap_rights(stdout, &ktr->cap_held);
		break;
	case CAPFAIL_INCREASE:
		/* requested more capabilities than fd already has */
		printf("attempt to increase capabilities from ");
		sysdecode_cap_rights(stdout, &ktr->cap_held);
		printf(" to ");
		sysdecode_cap_rights(stdout, &ktr->cap_needed);
		break;
	case CAPFAIL_SYSCALL:
		/* called restricted syscall */
		printf("disallowed system call");
		break;
	case CAPFAIL_LOOKUP:
		/* absolute or AT_FDCWD path, ".." path, etc. */
		printf("restricted VFS lookup");
		break;
	default:
		printf("unknown capability failure: ");
		sysdecode_cap_rights(stdout, &ktr->cap_needed);
		printf(" ");
		sysdecode_cap_rights(stdout, &ktr->cap_held);
		break;
	}
	printf("\n");
}