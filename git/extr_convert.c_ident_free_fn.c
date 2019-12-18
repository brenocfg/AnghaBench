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
struct stream_filter {int dummy; } ;
struct ident_filter {int /*<<< orphan*/  left; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct stream_filter*) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ident_free_fn(struct stream_filter *filter)
{
	struct ident_filter *ident = (struct ident_filter *)filter;
	strbuf_release(&ident->left);
	free(filter);
}