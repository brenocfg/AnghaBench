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
struct cuse_dev_entered {int is_local; } ;

/* Variables and functions */
 struct cuse_dev_entered* cuse_dev_get_entered () ; 

int
cuse_get_local(void)
{
	struct cuse_dev_entered *pe;

	pe = cuse_dev_get_entered();
	if (pe == NULL)
		return (0);

	return (pe->is_local);
}