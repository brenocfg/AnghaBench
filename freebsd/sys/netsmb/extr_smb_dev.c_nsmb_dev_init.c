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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/ * make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  nsmb_cdevsw ; 
 int /*<<< orphan*/ * nsmb_dev ; 

__attribute__((used)) static int
nsmb_dev_init(void)
{

	nsmb_dev = make_dev(&nsmb_cdevsw, 0, UID_ROOT, GID_OPERATOR,
	    0600, "nsmb");
	if (nsmb_dev == NULL)
		return (ENOMEM);  
	return (0);
}