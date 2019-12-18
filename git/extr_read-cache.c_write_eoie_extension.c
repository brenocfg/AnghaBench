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
typedef  unsigned char uint32_t ;
struct strbuf {int dummy; } ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
struct TYPE_2__ {int rawsz; int /*<<< orphan*/  (* final_fn ) (unsigned char*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int GIT_MAX_RAWSZ ; 
 int /*<<< orphan*/  put_be32 (unsigned char*,size_t) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static void write_eoie_extension(struct strbuf *sb, git_hash_ctx *eoie_context, size_t offset)
{
	uint32_t buffer;
	unsigned char hash[GIT_MAX_RAWSZ];

	/* offset */
	put_be32(&buffer, offset);
	strbuf_add(sb, &buffer, sizeof(uint32_t));

	/* hash */
	the_hash_algo->final_fn(hash, eoie_context);
	strbuf_add(sb, hash, the_hash_algo->rawsz);
}