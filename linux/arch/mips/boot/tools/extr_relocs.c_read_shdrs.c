#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sh_link; void* sh_entsize; void* sh_addralign; void* sh_info; void* sh_size; int /*<<< orphan*/  sh_offset; int /*<<< orphan*/  sh_addr; void* sh_flags; void* sh_type; void* sh_name; } ;
struct section {TYPE_1__ shdr; struct section* link; int /*<<< orphan*/  shdr_offset; } ;
typedef  int /*<<< orphan*/  shdr ;
struct TYPE_7__ {int e_shnum; int /*<<< orphan*/  e_shoff; } ;
struct TYPE_6__ {int /*<<< orphan*/  sh_entsize; int /*<<< orphan*/  sh_addralign; int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_link; int /*<<< orphan*/  sh_size; int /*<<< orphan*/  sh_offset; int /*<<< orphan*/  sh_addr; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ Elf_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 struct section* calloc (int,int) ; 
 int /*<<< orphan*/  die (char*,int,...) ; 
 TYPE_4__ ehdr ; 
 int /*<<< orphan*/  elf_addr_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_off_to_cpu (int /*<<< orphan*/ ) ; 
 void* elf_word_to_cpu (int /*<<< orphan*/ ) ; 
 void* elf_xword_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int fread (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 struct section* secs ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_shdrs(FILE *fp)
{
	int i;
	Elf_Shdr shdr;

	secs = calloc(ehdr.e_shnum, sizeof(struct section));
	if (!secs)
		die("Unable to allocate %d section headers\n", ehdr.e_shnum);

	if (fseek(fp, ehdr.e_shoff, SEEK_SET) < 0)
		die("Seek to %d failed: %s\n", ehdr.e_shoff, strerror(errno));

	for (i = 0; i < ehdr.e_shnum; i++) {
		struct section *sec = &secs[i];

		sec->shdr_offset = ftell(fp);
		if (fread(&shdr, sizeof(shdr), 1, fp) != 1)
			die("Cannot read ELF section headers %d/%d: %s\n",
			    i, ehdr.e_shnum, strerror(errno));
		sec->shdr.sh_name      = elf_word_to_cpu(shdr.sh_name);
		sec->shdr.sh_type      = elf_word_to_cpu(shdr.sh_type);
		sec->shdr.sh_flags     = elf_xword_to_cpu(shdr.sh_flags);
		sec->shdr.sh_addr      = elf_addr_to_cpu(shdr.sh_addr);
		sec->shdr.sh_offset    = elf_off_to_cpu(shdr.sh_offset);
		sec->shdr.sh_size      = elf_xword_to_cpu(shdr.sh_size);
		sec->shdr.sh_link      = elf_word_to_cpu(shdr.sh_link);
		sec->shdr.sh_info      = elf_word_to_cpu(shdr.sh_info);
		sec->shdr.sh_addralign = elf_xword_to_cpu(shdr.sh_addralign);
		sec->shdr.sh_entsize   = elf_xword_to_cpu(shdr.sh_entsize);
		if (sec->shdr.sh_link < ehdr.e_shnum)
			sec->link = &secs[sec->shdr.sh_link];
	}
}