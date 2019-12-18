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
struct ecore_hwfn {struct ecore_dev* p_dev; } ;
struct ecore_dev {int num_hwfns; struct ecore_hwfn* hwfns; } ;

/* Variables and functions */

__attribute__((used)) static int
qlnx_find_hwfn_index(struct ecore_hwfn *p_hwfn)
{
	int			i;
	struct ecore_dev	*cdev;

	cdev = p_hwfn->p_dev;

	for (i = 0; i < cdev->num_hwfns; i++) { 
		if (&cdev->hwfns[i] == p_hwfn)
			break;
	}

	if (i >= cdev->num_hwfns)
		return (-1);

	return (i);
}