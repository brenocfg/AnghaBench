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
struct blame_scoreboard {int dummy; } ;

/* Variables and functions */
 int OUTPUT_SHOW_NAME ; 
 int OUTPUT_SHOW_NUMBER ; 
 int OUTPUT_SHOW_SCORE ; 
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  find_alignment (struct blame_scoreboard*,int*) ; 
 int /*<<< orphan*/  output (struct blame_scoreboard*,int) ; 

__attribute__((used)) static void sanity_check_on_fail(struct blame_scoreboard *sb, int baa)
{
	int opt = OUTPUT_SHOW_SCORE | OUTPUT_SHOW_NUMBER | OUTPUT_SHOW_NAME;
	find_alignment(sb, &opt);
	output(sb, opt);
	die("Baa %d!", baa);
}