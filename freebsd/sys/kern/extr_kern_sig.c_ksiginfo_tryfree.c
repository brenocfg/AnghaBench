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
struct TYPE_4__ {int ksi_flags; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int KSI_EXT ; 
 int /*<<< orphan*/  ksiginfo_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static __inline int
ksiginfo_tryfree(ksiginfo_t *ksi)
{
	if (!(ksi->ksi_flags & KSI_EXT)) {
		uma_zfree(ksiginfo_zone, ksi);
		return (1);
	}
	return (0);
}