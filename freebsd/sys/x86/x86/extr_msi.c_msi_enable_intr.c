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
struct msi_intsrc {int /*<<< orphan*/  msi_vector; int /*<<< orphan*/  msi_cpu; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apic_enable_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
msi_enable_intr(struct intsrc *isrc)
{
	struct msi_intsrc *msi = (struct msi_intsrc *)isrc;

	apic_enable_vector(msi->msi_cpu, msi->msi_vector);
}