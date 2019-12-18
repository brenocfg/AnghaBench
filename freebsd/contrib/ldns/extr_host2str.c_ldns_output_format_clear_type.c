#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  bitmap; } ;
typedef  TYPE_1__ ldns_output_format_storage ;
typedef  int /*<<< orphan*/  ldns_output_format ;

/* Variables and functions */
 int LDNS_FMT_RFC3597 ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_nsec_bitmap_clear_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_output_format_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ldns_rdf_bitmap_known_rr_types (int /*<<< orphan*/ *) ; 

ldns_status
ldns_output_format_clear_type(ldns_output_format* fmt, ldns_rr_type t)
{
	ldns_output_format_storage* fmt_st = (ldns_output_format_storage*)fmt;
	ldns_status s;
	
	assert(fmt != NULL);

	if (!(fmt_st->flags & LDNS_FMT_RFC3597)) {
		ldns_output_format_set(fmt, LDNS_FMT_RFC3597);
	}
	if (! fmt_st->bitmap) {
		s = ldns_rdf_bitmap_known_rr_types(&fmt_st->bitmap);
		if (s != LDNS_STATUS_OK) {
			return s;
		}
	}
	return ldns_nsec_bitmap_clear_type(fmt_st->bitmap, t);
}