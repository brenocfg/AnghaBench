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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  mac_init_label (struct label*) ; 

__attribute__((used)) static int
mac_labelzone_ctor(void *mem, int size, void *arg, int flags)
{
	struct label *label;

	KASSERT(size == sizeof(*label), ("mac_labelzone_ctor: wrong size\n"));
	label = mem;
	mac_init_label(label);
	return (0);
}