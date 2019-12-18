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
struct TYPE_2__ {int /*<<< orphan*/  rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_add (struct strbuf*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned int,unsigned int,char const*,char) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static void write_tree_entry(struct strbuf *buf, unsigned int mode,
		const char *path, unsigned int path_len, const
		unsigned char *hash)
{
	strbuf_addf(buf, "%o %.*s%c", mode, path_len, path, '\0');
	strbuf_add(buf, hash, the_hash_algo->rawsz);
}