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
typedef  int /*<<< orphan*/  git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int git_index_add_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t) ; 

int git_index_add_frombuffer(
    git_index *index, const git_index_entry *source_entry,
    const void *buffer, size_t len)
{
	return git_index_add_from_buffer(index, source_entry, buffer, len);
}