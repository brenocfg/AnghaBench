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
struct dl_phdr_info {int dummy; } ;
struct cxa_thread_dtor {int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  obj; int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 scalar_t__ __elf_phdr_match_addr (struct dl_phdr_info*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 scalar_t__ _rtld_addr_phdr (int /*<<< orphan*/ ,struct dl_phdr_info*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
walk_cb_call(struct cxa_thread_dtor *dtor)
{
	struct dl_phdr_info phdr_info;

	if (_rtld_addr_phdr(dtor->dso, &phdr_info) &&
	    __elf_phdr_match_addr(&phdr_info, dtor->func))
		dtor->func(dtor->obj);
	else
		fprintf(stderr, "__cxa_thread_call_dtors: dtr %p from "
		    "unloaded dso, skipping\n", (void *)(dtor->func));
}