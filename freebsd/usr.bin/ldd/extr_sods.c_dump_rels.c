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
struct relocation_info {unsigned int r_length; unsigned long r_symbolnum; scalar_t__ r_copy; scalar_t__ r_jmptable; scalar_t__ r_baserel; scalar_t__ r_extern; scalar_t__ r_pcrel; scalar_t__ r_relative; scalar_t__ r_address; } ;
struct TYPE_2__ {unsigned long a_text; unsigned long a_data; } ;

/* Variables and functions */
 scalar_t__ align_long (scalar_t__) ; 
 scalar_t__ align_short (scalar_t__) ; 
 TYPE_1__* ex ; 
 unsigned long origin ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ text_addr ; 

__attribute__((used)) static void
dump_rels(const char *label, const struct relocation_info *base,
    unsigned long count, const char *(*name)(unsigned long),
    unsigned char *sym_used_flags)
{
    unsigned long i;

    printf("  %s:\n", label);
    for (i = 0;  i < count;  ++i) {
	const struct relocation_info *r = &base[i];
	unsigned int size;
	char contents[16];

	size = 1u << r->r_length;

	if (origin <= (unsigned long)r->r_address
	  && (unsigned long)r->r_address < origin + ex->a_text + ex->a_data
	  && 1 <= size && size <= 4) {
	    /*
	     * XXX - This can cause unaligned accesses.  OK for the
	     * i386, not so for other architectures.
	     */
	    switch (size) {
	    case 1:
		snprintf(contents, sizeof contents, "      [%02x]",
		  *(unsigned const char *)(text_addr + r->r_address));
		break;
	    case 2:
		snprintf(contents, sizeof contents, "    [%04x]",
			 *(unsigned const short *)
			 align_short(text_addr + r->r_address));
		break;
	    case 4:
		snprintf(contents, sizeof contents, "[%08lx]",
			 *(unsigned const long *)
			 align_long(text_addr + r->r_address));
		break;
	    }
	} else
	    snprintf(contents, sizeof contents, "          ");

	printf("    %6lu %8x/%u %s %c%c%c%c%c%c", i,
	    r->r_address, size,
	    contents,
	    r->r_extern   ? 'e' : '-',
	    r->r_jmptable ? 'j' : '-',
	    r->r_relative ? 'r' : '-',
	    r->r_baserel  ? 'b' : '-',
	    r->r_pcrel    ? 'p' : '-',
	    r->r_copy     ? 'c' : '-');

	if (r->r_extern || r->r_baserel || r->r_jmptable || r->r_copy) {
	    printf(" %4u %s", r->r_symbolnum, name(r->r_symbolnum));
	    sym_used_flags[r->r_symbolnum] = 1;
	}

	printf("\n");
    }
}