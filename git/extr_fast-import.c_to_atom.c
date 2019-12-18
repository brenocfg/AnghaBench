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
struct atom_str {unsigned short str_len; struct atom_str* next_atom; scalar_t__* str_dat; } ;

/* Variables and functions */
 int /*<<< orphan*/  atom_cnt ; 
 struct atom_str** atom_table ; 
 unsigned int atom_table_sz ; 
 int /*<<< orphan*/  fi_mem_pool ; 
 unsigned int hc_str (char const*,unsigned short) ; 
 struct atom_str* mem_pool_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,unsigned short) ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__*,unsigned short) ; 

__attribute__((used)) static struct atom_str *to_atom(const char *s, unsigned short len)
{
	unsigned int hc = hc_str(s, len) % atom_table_sz;
	struct atom_str *c;

	for (c = atom_table[hc]; c; c = c->next_atom)
		if (c->str_len == len && !strncmp(s, c->str_dat, len))
			return c;

	c = mem_pool_alloc(&fi_mem_pool, sizeof(struct atom_str) + len + 1);
	c->str_len = len;
	memcpy(c->str_dat, s, len);
	c->str_dat[len] = 0;
	c->next_atom = atom_table[hc];
	atom_table[hc] = c;
	atom_cnt++;
	return c;
}