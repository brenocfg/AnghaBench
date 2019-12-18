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
typedef  enum MAD_FIELDS { ____Placeholder_MAD_FIELDS } MAD_FIELDS ;

/* Variables and functions */
 int /*<<< orphan*/  IBWARN (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SUP_MAX ; 
 int /*<<< orphan*/  mad_field_name (int) ; 
 scalar_t__ sup_total ; 
 int* suppressed_fields ; 

__attribute__((used)) static void add_suppressed(enum MAD_FIELDS field)
{
	if (sup_total >= SUP_MAX) {
		IBWARN("Maximum (%d) fields have been suppressed; skipping %s",
		       sup_total, mad_field_name(field));
		return;
	}
	suppressed_fields[sup_total++] = field;
}