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
struct TYPE_2__ {scalar_t__* e_ident; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf64_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS32 ; 
 scalar_t__ ELFCLASS64 ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  go32 (void*,size_t,void*,size_t,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  go64 (void*,size_t,void*,size_t,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void go(void *raw_addr, size_t raw_len,
	       void *stripped_addr, size_t stripped_len,
	       FILE *outfile, const char *name)
{
	Elf64_Ehdr *hdr = (Elf64_Ehdr *)raw_addr;

	if (hdr->e_ident[EI_CLASS] == ELFCLASS64) {
		go64(raw_addr, raw_len, stripped_addr, stripped_len,
		     outfile, name);
	} else if (hdr->e_ident[EI_CLASS] == ELFCLASS32) {
		go32(raw_addr, raw_len, stripped_addr, stripped_len,
		     outfile, name);
	} else {
		fail("unknown ELF class\n");
	}
}