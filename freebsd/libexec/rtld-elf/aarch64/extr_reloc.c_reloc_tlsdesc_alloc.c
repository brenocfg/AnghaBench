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
struct tls_data {int tls_index; int /*<<< orphan*/  tls_offs; int /*<<< orphan*/  dtv_gen; } ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  tls_dtv_generation ; 
 struct tls_data* xmalloc (int) ; 

__attribute__((used)) static Elf_Addr
reloc_tlsdesc_alloc(int tlsindex, Elf_Addr tlsoffs)
{
	struct tls_data *tlsdesc;

	tlsdesc = xmalloc(sizeof(struct tls_data));
	tlsdesc->dtv_gen = tls_dtv_generation;
	tlsdesc->tls_index = tlsindex;
	tlsdesc->tls_offs = tlsoffs;

	return ((Elf_Addr)tlsdesc);
}