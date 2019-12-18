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
struct cuse_dev_entered {int cmd; struct cuse_dev* cdev; } ;
struct cuse_dev {int dummy; } ;

/* Variables and functions */
 struct cuse_dev_entered* cuse_dev_get_entered () ; 

struct cuse_dev *
cuse_dev_get_current(int *pcmd)
{
	struct cuse_dev_entered *pe;

	pe = cuse_dev_get_entered();
	if (pe == NULL) {
		if (pcmd != NULL)
			*pcmd = 0;
		return (NULL);
	}
	if (pcmd != NULL)
		*pcmd = pe->cmd;
	return (pe->cdev);
}