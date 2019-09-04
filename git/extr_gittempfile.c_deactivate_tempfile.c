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
struct tempfile {int /*<<< orphan*/  list; int /*<<< orphan*/  filename; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tempfile*) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  volatile_list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deactivate_tempfile(struct tempfile *tempfile)
{
	tempfile->active = 0;
	strbuf_release(&tempfile->filename);
	volatile_list_del(&tempfile->list);
	free(tempfile);
}