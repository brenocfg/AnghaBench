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
struct TYPE_2__ {int /*<<< orphan*/  coff_number_of_sections; } ;
struct pe_header {scalar_t__ pe_signature; TYPE_1__ pe_coff; } ;
struct executable {scalar_t__ x_buf; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ PE_SIGNATURE ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  parse_optional (struct executable*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_check (struct executable*,scalar_t__,int,char*) ; 

__attribute__((used)) static void
parse_pe(struct executable *x, off_t off)
{
	const struct pe_header *pe;

	//printf("PE offset %zd, PE size %zd\n", off, sizeof(*pe));

	range_check(x, off, sizeof(*pe), "PE header");

	pe = (struct pe_header *)(x->x_buf + off);
	if (pe->pe_signature != PE_SIGNATURE)
		errx(1, "wrong PE signature 0x%x", pe->pe_signature);

	//printf("Number of sections: %d\n", pe->pe_coff.coff_number_of_sections);

	parse_optional(x, off + sizeof(*pe),
	    pe->pe_coff.coff_number_of_sections);
}