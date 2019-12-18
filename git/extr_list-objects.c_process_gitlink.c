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
struct traversal_context {int dummy; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void process_gitlink(struct traversal_context *ctx,
			    const unsigned char *sha1,
			    struct strbuf *path,
			    const char *name)
{
	/* Nothing to do */
}