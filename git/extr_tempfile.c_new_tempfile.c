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
struct tempfile {int fd; int /*<<< orphan*/  filename; int /*<<< orphan*/  list; scalar_t__ owner; scalar_t__ active; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tempfile* xmalloc (int) ; 

__attribute__((used)) static struct tempfile *new_tempfile(void)
{
	struct tempfile *tempfile = xmalloc(sizeof(*tempfile));
	tempfile->fd = -1;
	tempfile->fp = NULL;
	tempfile->active = 0;
	tempfile->owner = 0;
	INIT_LIST_HEAD(&tempfile->list);
	strbuf_init(&tempfile->filename, 0);
	return tempfile;
}