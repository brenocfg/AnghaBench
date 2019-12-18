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
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  domain_enum ;

/* Variables and functions */
 struct block* block_static_block (struct block const*) ; 
 struct symbol* lookup_symbol_aux_block (char const*,char const*,struct block const*,int /*<<< orphan*/  const,struct symtab**) ; 

struct symbol *
lookup_symbol_static (const char *name,
		      const char *linkage_name,
		      const struct block *block,
		      const domain_enum domain,
		      struct symtab **symtab)
{
  const struct block *static_block = block_static_block (block);

  if (static_block != NULL)
    return lookup_symbol_aux_block (name, linkage_name, static_block,
				    domain, symtab);
  else
    return NULL;
}