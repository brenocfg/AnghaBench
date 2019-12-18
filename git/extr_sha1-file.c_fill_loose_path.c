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
struct strbuf {int dummy; } ;
struct object_id {unsigned int* hash; } ;
struct TYPE_2__ {int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static void fill_loose_path(struct strbuf *buf, const struct object_id *oid)
{
	int i;
	for (i = 0; i < the_hash_algo->rawsz; i++) {
		static char hex[] = "0123456789abcdef";
		unsigned int val = oid->hash[i];
		strbuf_addch(buf, hex[val >> 4]);
		strbuf_addch(buf, hex[val & 0xf]);
		if (!i)
			strbuf_addch(buf, '/');
	}
}