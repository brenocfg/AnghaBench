#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pmfd; scalar_t__ rawdump; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 scalar_t__ memcmp (char**,char*,int) ; 
 int pread (int /*<<< orphan*/ ,char**,int,int /*<<< orphan*/ ) ; 

int
_kvm_is_minidump(kvm_t *kd)
{
	char minihdr[8];

	if (kd->rawdump)
		return (0);
	if (pread(kd->pmfd, &minihdr, 8, 0) == 8 &&
	    memcmp(&minihdr, "minidump", 8) == 0)
		return (1);
	return (0);
}