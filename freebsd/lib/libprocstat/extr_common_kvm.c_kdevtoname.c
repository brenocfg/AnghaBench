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
struct cdev {int /*<<< orphan*/  si_name; } ;
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 scalar_t__ SPECNAMELEN ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct cdev*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

int
kdevtoname(kvm_t *kd, struct cdev *dev, char *buf)
{
	struct cdev si;

	assert(buf);
	if (!kvm_read_all(kd, (unsigned long)dev, &si, sizeof(si)))
		return (1);
	strlcpy(buf, si.si_name, SPECNAMELEN + 1);
	return (0);
}