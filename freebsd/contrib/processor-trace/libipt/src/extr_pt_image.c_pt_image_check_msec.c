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
typedef  scalar_t__ uint64_t ;
struct pt_mapped_section {int dummy; } ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int pt_asid_match (struct pt_asid const*,struct pt_asid const*) ; 
 struct pt_asid* pt_msec_asid (struct pt_mapped_section const*) ; 
 scalar_t__ pt_msec_begin (struct pt_mapped_section const*) ; 
 scalar_t__ pt_msec_end (struct pt_mapped_section const*) ; 
 int pte_internal ; 
 int pte_nomap ; 

__attribute__((used)) static inline int pt_image_check_msec(const struct pt_mapped_section *msec,
				      const struct pt_asid *asid,
				      uint64_t vaddr)
{
	const struct pt_asid *masid;
	uint64_t begin, end;
	int errcode;

	if (!msec)
		return -pte_internal;

	begin = pt_msec_begin(msec);
	end = pt_msec_end(msec);
	if (vaddr < begin || end <= vaddr)
		return -pte_nomap;

	masid = pt_msec_asid(msec);
	errcode = pt_asid_match(masid, asid);
	if (errcode <= 0) {
		if (!errcode)
			errcode = -pte_nomap;

		return errcode;
	}

	return 0;
}