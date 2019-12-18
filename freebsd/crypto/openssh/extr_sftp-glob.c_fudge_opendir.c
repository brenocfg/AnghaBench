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
struct SFTP_OPENDIR {scalar_t__ offset; int /*<<< orphan*/  dir; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 TYPE_1__ cur ; 
 scalar_t__ do_readdir (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct SFTP_OPENDIR*) ; 
 struct SFTP_OPENDIR* xcalloc (int,int) ; 

__attribute__((used)) static void *
fudge_opendir(const char *path)
{
	struct SFTP_OPENDIR *r;

	r = xcalloc(1, sizeof(*r));

	if (do_readdir(cur.conn, (char *)path, &r->dir)) {
		free(r);
		return(NULL);
	}

	r->offset = 0;

	return((void *)r);
}