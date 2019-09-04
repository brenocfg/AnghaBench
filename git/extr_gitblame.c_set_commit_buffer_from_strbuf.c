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
struct strbuf {int dummy; } ;
struct repository {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_commit_buffer (struct repository*,struct commit*,void*,size_t) ; 
 void* strbuf_detach (struct strbuf*,size_t*) ; 

__attribute__((used)) static void set_commit_buffer_from_strbuf(struct repository *r,
					  struct commit *c,
					  struct strbuf *sb)
{
	size_t len;
	void *buf = strbuf_detach(sb, &len);
	set_commit_buffer(r, c, buf, len);
}