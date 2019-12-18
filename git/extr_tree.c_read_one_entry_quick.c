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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CACHE_JUST_APPEND ; 
 int read_one_entry_opt (struct index_state*,struct object_id const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_one_entry_quick(const struct object_id *oid, struct strbuf *base,
				const char *pathname, unsigned mode, int stage,
				void *context)
{
	struct index_state *istate = context;
	return read_one_entry_opt(istate, oid, base->buf, base->len, pathname,
				  mode, stage,
				  ADD_CACHE_JUST_APPEND);
}