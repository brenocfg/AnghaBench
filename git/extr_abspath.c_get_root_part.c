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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  convert_slashes (int /*<<< orphan*/ ) ; 
 int offset_1st_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void get_root_part(struct strbuf *resolved, struct strbuf *remaining)
{
	int offset = offset_1st_component(remaining->buf);

	strbuf_reset(resolved);
	strbuf_add(resolved, remaining->buf, offset);
#ifdef GIT_WINDOWS_NATIVE
	convert_slashes(resolved->buf);
#endif
	strbuf_remove(remaining, 0, offset);
}