#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* src; char* dst; scalar_t__ force; } ;
typedef  TYPE_1__ git_refspec ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 

int git_refspec__serialize(git_buf *out, const git_refspec *refspec)
{
	if (refspec->force)
		git_buf_putc(out, '+');

	git_buf_printf(out, "%s:%s",
		refspec->src != NULL ? refspec->src : "",
		refspec->dst != NULL ? refspec->dst : "");

	return git_buf_oom(out) == false;
}