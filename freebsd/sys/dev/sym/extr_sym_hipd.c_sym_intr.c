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
typedef  void* hcb_p ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_TINY ; 
 int /*<<< orphan*/  SYM_LOCK () ; 
 int /*<<< orphan*/  SYM_UNLOCK () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sym_intr1 (void*) ; 

__attribute__((used)) static void sym_intr(void *arg)
{
	hcb_p np = arg;

	SYM_LOCK();

	if (DEBUG_FLAGS & DEBUG_TINY) printf ("[");
	sym_intr1((hcb_p) arg);
	if (DEBUG_FLAGS & DEBUG_TINY) printf ("]");

	SYM_UNLOCK();
}