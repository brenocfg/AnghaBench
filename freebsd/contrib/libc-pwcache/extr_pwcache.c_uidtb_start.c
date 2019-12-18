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
typedef  int /*<<< orphan*/  UIDC ;

/* Variables and functions */
 int /*<<< orphan*/  UID_SZ ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** uidtb ; 
 scalar_t__ uidtb_fail ; 

__attribute__((used)) static int
uidtb_start(void)
{

	if (uidtb != NULL)
		return (0);
	if (uidtb_fail)
		return (-1);
	if ((uidtb = (UIDC **)calloc(UID_SZ, sizeof(UIDC *))) == NULL) {
		++uidtb_fail;
		return (-1);
	}
	return (0);
}