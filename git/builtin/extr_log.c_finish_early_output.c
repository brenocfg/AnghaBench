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
struct rev_info {int /*<<< orphan*/  commits; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int estimate_commit_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_early_header (struct rev_info*,char*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finish_early_output(struct rev_info *rev)
{
	int n = estimate_commit_count(rev->commits);
	signal(SIGALRM, SIG_IGN);
	show_early_header(rev, "done", n);
}