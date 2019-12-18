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
typedef  int /*<<< orphan*/  ddt_key_t ;
struct TYPE_4__ {int /*<<< orphan*/  dde_key; int /*<<< orphan*/  dde_cv; } ;
typedef  TYPE_1__ ddt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ddt_entry_t *
ddt_alloc(const ddt_key_t *ddk)
{
	ddt_entry_t *dde;

	dde = kmem_zalloc(sizeof (ddt_entry_t), KM_SLEEP);
	cv_init(&dde->dde_cv, NULL, CV_DEFAULT, NULL);

	dde->dde_key = *ddk;

	return (dde);
}