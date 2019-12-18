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
struct uni {size_t custat; size_t glob_start; size_t glob_respond; int /*<<< orphan*/  arg; TYPE_1__* funcs; int /*<<< orphan*/  delq; int /*<<< orphan*/  workq; scalar_t__ working; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* status ) (struct uni*,int /*<<< orphan*/ ,void*,char*,char*) ;} ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 char** custat_names ; 
 char** globstat_names ; 
 int /*<<< orphan*/  stub1 (struct uni*,int /*<<< orphan*/ ,void*,char*,char*) ; 
 int /*<<< orphan*/  stub2 (struct uni*,int /*<<< orphan*/ ,void*,char*,char*) ; 
 int /*<<< orphan*/  stub3 (struct uni*,int /*<<< orphan*/ ,void*,char*,char*) ; 
 int /*<<< orphan*/  stub4 (struct uni*,int /*<<< orphan*/ ,void*,char*,char*) ; 
 int /*<<< orphan*/  stub5 (struct uni*,int /*<<< orphan*/ ,void*,char*,char*) ; 
 int /*<<< orphan*/  stub6 (struct uni*,int /*<<< orphan*/ ,void*,char*,char*) ; 

void
uni_status(struct uni *uni, void *arg)
{
	uni->funcs->status(uni, uni->arg, arg,
	    "working: %s\n", uni->working ? "yes" : "no");
	uni->funcs->status(uni, uni->arg, arg,
	    "work queue: %sempty\n", TAILQ_EMPTY(&uni->workq)? "" : "not ");
	uni->funcs->status(uni, uni->arg, arg,
	    "delayed work queue: %sempty\n",
	    TAILQ_EMPTY(&uni->delq)? "" : "not ");
	uni->funcs->status(uni, uni->arg, arg,
	    "coordinator: %s\n", custat_names[uni->custat]);
	uni->funcs->status(uni, uni->arg, arg,
	    "reset-start: %s\n", globstat_names[uni->glob_start]);
	uni->funcs->status(uni, uni->arg, arg,
	    "reset-respond: %s\n", globstat_names[uni->glob_respond]);
}