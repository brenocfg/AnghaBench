#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct process {scalar_t__ p_index; scalar_t__ p_procid; scalar_t__ p_jobid; int /*<<< orphan*/  p_command; struct process* p_next; } ;
typedef  int Strbuf ;
struct TYPE_2__ {struct process* p_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_append (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE (int*) ; 
 scalar_t__ pmaxindex ; 
 TYPE_1__ proclist ; 
 scalar_t__ tw_index ; 

int
tw_job_next(struct Strbuf *res, struct Strbuf *dir, int *flags)
{
    struct process *j;

    USE(dir);
    USE(flags);
    for (;tw_index <= pmaxindex; tw_index++) {
	for (j = proclist.p_next; j != NULL; j = j->p_next)
	    if (j->p_index == tw_index && j->p_procid == j->p_jobid)
		break;
	if (j == NULL) 
	    continue;
	Strbuf_append(res, j->p_command);
	tw_index++;
	return 1;
    }
    return 0;
}