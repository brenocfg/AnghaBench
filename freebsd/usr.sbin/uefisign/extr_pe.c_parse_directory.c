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
struct pe_directory_entry {int pde_size; scalar_t__ pde_rva; } ;
struct executable {scalar_t__ x_headers_len; int x_certificate_entry_len; scalar_t__ x_buf; scalar_t__ x_certificate_entry_off; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int PE_DIRECTORY_ENTRY_CERTIFICATE ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int i ; 
 void parse_section_table (struct executable*,scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  range_check (struct executable*,scalar_t__,int,char*) ; 

__attribute__((used)) static void
parse_directory(struct executable *x, off_t off,
    int number_of_rva_and_sizes, int number_of_sections)
{
	//int i;
	const struct pe_directory_entry *pde;

	//printf("Data Directory at offset %zd\n", off);

	if (number_of_rva_and_sizes <= PE_DIRECTORY_ENTRY_CERTIFICATE) {
		errx(1, "wrong NumberOfRvaAndSizes %d; should be at least %d",
		    number_of_rva_and_sizes, PE_DIRECTORY_ENTRY_CERTIFICATE);
	}

	range_check(x, off, sizeof(*pde) * number_of_rva_and_sizes,
	    "PE Data Directory");
	if (x->x_headers_len <= off + sizeof(*pde) * number_of_rva_and_sizes)
		errx(1, "PE Data Directory outside of headers");

	x->x_certificate_entry_off =
	    off + sizeof(*pde) * PE_DIRECTORY_ENTRY_CERTIFICATE;
	x->x_certificate_entry_len = sizeof(*pde);
#if 0
	printf("certificate directory entry at offset %zd, len %zd\n",
	    x->x_certificate_entry_off, x->x_certificate_entry_len);

	pde = (struct pe_directory_entry *)(x->x_buf + off);
	for (i = 0; i < number_of_rva_and_sizes; i++) {
		printf("rva %zd, size %zd\n", pde->pde_rva, pde->pde_size);
		pde++;
	}
#endif

	return (parse_section_table(x,
	    off + sizeof(*pde) * number_of_rva_and_sizes, number_of_sections));
}