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
struct padata_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  padata_free (struct padata_instance*) ; 
 int /*<<< orphan*/  padata_stop (struct padata_instance*) ; 

__attribute__((used)) static void pcrypt_fini_padata(struct padata_instance *pinst)
{
	padata_stop(pinst);
	padata_free(pinst);
}