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
struct objfile {int /*<<< orphan*/  md; int /*<<< orphan*/  demangled_names_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  htab_create_alloc_ex (int,int /*<<< orphan*/ ,int (*) (void const*,void const*),int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_string ; 
 scalar_t__ streq ; 
 int /*<<< orphan*/  xmcalloc ; 
 int /*<<< orphan*/  xmfree ; 

__attribute__((used)) static void
create_demangled_names_hash (struct objfile *objfile)
{
  /* Choose 256 as the starting size of the hash table, somewhat arbitrarily.
     The hash table code will round this up to the next prime number. 
     Choosing a much larger table size wastes memory, and saves only about
     1% in symbol reading.  */

  objfile->demangled_names_hash = htab_create_alloc_ex
    (256, htab_hash_string, (int (*) (const void *, const void *)) streq,
     NULL, objfile->md, xmcalloc, xmfree);
}