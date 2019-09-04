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

/* Variables and functions */
 int EOF ; 
 int fgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skip_optional_lf(void)
{
	int term_char = fgetc(stdin);
	if (term_char != '\n' && term_char != EOF)
		ungetc(term_char, stdin);
}