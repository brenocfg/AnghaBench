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
struct merge_options {TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  orig_index; } ;

/* Variables and functions */
 int index_name_pos (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int was_tracked(struct merge_options *opt, const char *path)
{
	int pos = index_name_pos(&opt->priv->orig_index, path, strlen(path));

	if (0 <= pos)
		/* we were tracking this path before the merge */
		return 1;

	return 0;
}