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
struct sdei_event {int dummy; } ;
struct sdei_crosscall_args {int first_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  CROSSCALL_INIT (struct sdei_crosscall_args,struct sdei_event*) ; 
 int /*<<< orphan*/  on_each_cpu (void*,struct sdei_crosscall_args*,int) ; 

__attribute__((used)) static inline int sdei_do_cross_call(void *fn, struct sdei_event * event)
{
	struct sdei_crosscall_args arg;

	CROSSCALL_INIT(arg, event);
	on_each_cpu(fn, &arg, true);

	return arg.first_error;
}