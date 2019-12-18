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
struct thread {struct linux_emuldata* td_emuldata; } ;
struct linux_emuldata {int dummy; } ;

/* Variables and functions */

struct linux_emuldata *
em_find(struct thread *td)
{
	struct linux_emuldata *em;

	em = td->td_emuldata;

	return (em);
}