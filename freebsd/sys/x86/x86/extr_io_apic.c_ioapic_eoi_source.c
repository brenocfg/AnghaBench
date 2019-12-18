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
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ioapic_eoi_source (struct intsrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ioapic_eoi_source(struct intsrc *isrc)
{

	_ioapic_eoi_source(isrc, 0);
}