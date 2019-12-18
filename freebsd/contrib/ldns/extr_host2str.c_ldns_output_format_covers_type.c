#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rr_type ;
struct TYPE_4__ {scalar_t__ bitmap; } ;
typedef  TYPE_1__ ldns_output_format_storage ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_2__ ldns_output_format ;

/* Variables and functions */
 int LDNS_FMT_RFC3597 ; 
 scalar_t__ ldns_nsec_bitmap_covers_type (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ldns_output_format_covers_type(const ldns_output_format* fmt, ldns_rr_type t)
{
	return fmt && (fmt->flags & LDNS_FMT_RFC3597) &&
		((ldns_output_format_storage*)fmt)->bitmap &&
		ldns_nsec_bitmap_covers_type(
				((ldns_output_format_storage*)fmt)->bitmap, t);
}