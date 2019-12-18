#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * module; int /*<<< orphan*/  optv; int /*<<< orphan*/  optc; struct TYPE_4__* next; } ;
typedef  TYPE_1__ pam_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  FREEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openpam_release_module (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
openpam_destroy_chain(pam_chain_t *chain)
{

	if (chain == NULL)
		return;
	openpam_destroy_chain(chain->next);
	chain->next = NULL;
	FREEV(chain->optc, chain->optv);
	openpam_release_module(chain->module);
	chain->module = NULL;
	FREE(chain);
}