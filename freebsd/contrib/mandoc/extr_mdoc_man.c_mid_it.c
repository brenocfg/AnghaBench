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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__* Bl_stack ; 
 int Bl_stack_len ; 
 int* Bl_stack_post ; 
 int /*<<< orphan*/  MMAN_Bk_susp ; 
 int /*<<< orphan*/  print_line (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_word (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

__attribute__((used)) static void
mid_it(void)
{
	char		 buf[24];

	/* Nothing to do outside a list. */
	if (0 == Bl_stack_len || 0 == Bl_stack[Bl_stack_len - 1])
		return;

	/* The indentation has already been set up. */
	if (Bl_stack_post[Bl_stack_len - 1])
		return;

	/* Restore the indentation of the enclosing list. */
	print_line(".RS", MMAN_Bk_susp);
	(void)snprintf(buf, sizeof(buf), "%dn",
	    Bl_stack[Bl_stack_len - 1]);
	print_word(buf);

	/* Remeber to close out this .RS block later. */
	Bl_stack_post[Bl_stack_len - 1] = 1;
}