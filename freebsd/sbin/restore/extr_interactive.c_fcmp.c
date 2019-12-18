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
struct afile {int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int strcoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fcmp(const void *f1, const void *f2)
{
	return (strcoll(((struct afile *)f1)->fname,
	    ((struct afile *)f2)->fname));
}