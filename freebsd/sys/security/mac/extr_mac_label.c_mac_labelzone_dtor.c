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
 int /*<<< orphan*/  mac_destroy_label (struct label*) ; 

__attribute__((used)) static void
mac_labelzone_dtor(void *mem, int size, void *arg)
{
	struct label *label;

	KASSERT(size == sizeof(*label), ("mac_labelzone_dtor: wrong size\n"));
	label = mem;
	mac_destroy_label(label);
}