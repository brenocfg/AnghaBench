#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  len; } ;
struct index_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ mmfile_t ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ renormalize_buffer (struct index_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void normalize_file(mmfile_t *mm, const char *path, struct index_state *istate)
{
	struct strbuf strbuf = STRBUF_INIT;
	if (renormalize_buffer(istate, path, mm->ptr, mm->size, &strbuf)) {
		free(mm->ptr);
		mm->size = strbuf.len;
		mm->ptr = strbuf_detach(&strbuf, NULL);
	}
}