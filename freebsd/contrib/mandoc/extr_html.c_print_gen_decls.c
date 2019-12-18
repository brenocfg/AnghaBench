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
struct html {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_endline (struct html*) ; 
 int /*<<< orphan*/  print_word (struct html*,char*) ; 

void
print_gen_decls(struct html *h)
{
	print_word(h, "<!DOCTYPE html>");
	print_endline(h);
}