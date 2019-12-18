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
struct jump_entry {int dummy; } ;
struct insn {int dummy; } ;

/* Variables and functions */
 scalar_t__ jump_entry_code (struct jump_entry*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_emerg (char*,unsigned char*,...) ; 

__attribute__((used)) static void jump_label_bug(struct jump_entry *entry, struct insn *expected,
			   struct insn *new)
{
	unsigned char *ipc = (unsigned char *)jump_entry_code(entry);
	unsigned char *ipe = (unsigned char *)expected;
	unsigned char *ipn = (unsigned char *)new;

	pr_emerg("Jump label code mismatch at %pS [%p]\n", ipc, ipc);
	pr_emerg("Found:    %6ph\n", ipc);
	pr_emerg("Expected: %6ph\n", ipe);
	pr_emerg("New:      %6ph\n", ipn);
	panic("Corrupted kernel text");
}