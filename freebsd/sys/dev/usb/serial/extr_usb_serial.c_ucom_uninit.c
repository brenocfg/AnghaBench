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
struct unrhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  delete_unrhdr (struct unrhdr*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_mtx ; 
 struct unrhdr* ucom_unrhdr ; 

__attribute__((used)) static void
ucom_uninit(void *arg)
{
	struct unrhdr *hdr;
	hdr = ucom_unrhdr;
	ucom_unrhdr = NULL;

	DPRINTF("\n");

	if (hdr != NULL)
		delete_unrhdr(hdr);

	mtx_destroy(&ucom_mtx);
}