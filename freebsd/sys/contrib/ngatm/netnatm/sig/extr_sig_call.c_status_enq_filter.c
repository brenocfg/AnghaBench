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
struct sig {scalar_t__ type; scalar_t__ sig; struct call* call; } ;
struct call {int dummy; } ;

/* Variables and functions */
 scalar_t__ SIGC_SEND_STATUS_ENQ ; 
 scalar_t__ SIG_CALL ; 

__attribute__((used)) static int
status_enq_filter(struct sig *sig, void *arg)
{
	return (sig->type == SIG_CALL &&
	    (struct call *)arg == sig->call &&
	    sig->sig == SIGC_SEND_STATUS_ENQ);
}