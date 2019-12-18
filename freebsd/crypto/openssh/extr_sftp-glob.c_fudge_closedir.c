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
struct SFTP_OPENDIR {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct SFTP_OPENDIR*) ; 
 int /*<<< orphan*/  free_sftp_dirents (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fudge_closedir(struct SFTP_OPENDIR *od)
{
	free_sftp_dirents(od->dir);
	free(od);
}