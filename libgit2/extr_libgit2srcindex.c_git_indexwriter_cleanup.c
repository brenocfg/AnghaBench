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
struct TYPE_3__ {int /*<<< orphan*/ * index; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ git_indexwriter ;

/* Variables and functions */
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 

void git_indexwriter_cleanup(git_indexwriter *writer)
{
	git_filebuf_cleanup(&writer->file);

	git_index_free(writer->index);
	writer->index = NULL;
}