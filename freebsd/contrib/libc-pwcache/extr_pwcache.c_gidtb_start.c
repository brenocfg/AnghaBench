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
typedef  int /*<<< orphan*/  GIDC ;

/* Variables and functions */
 int /*<<< orphan*/  GID_SZ ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** gidtb ; 
 scalar_t__ gidtb_fail ; 

__attribute__((used)) static int
gidtb_start(void)
{

	if (gidtb != NULL)
		return (0);
	if (gidtb_fail)
		return (-1);
	if ((gidtb = (GIDC **)calloc(GID_SZ, sizeof(GIDC *))) == NULL) {
		++gidtb_fail;
		return (-1);
	}
	return (0);
}