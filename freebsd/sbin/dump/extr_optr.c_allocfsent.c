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
struct fstab {int /*<<< orphan*/  fs_freq; int /*<<< orphan*/  fs_passno; int /*<<< orphan*/ * fs_spec; int /*<<< orphan*/ * fs_type; int /*<<< orphan*/ * fs_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  quit (char*,int /*<<< orphan*/ ) ; 
 void* strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

struct fstab *
allocfsent(const struct fstab *fs)
{
	struct fstab *new;

	new = (struct fstab *)malloc(sizeof (*fs));
	if (new == NULL ||
	    (new->fs_file = strdup(fs->fs_file)) == NULL ||
	    (new->fs_type = strdup(fs->fs_type)) == NULL ||
	    (new->fs_spec = strdup(fs->fs_spec)) == NULL)
		quit("%s\n", strerror(errno));
	new->fs_passno = fs->fs_passno;
	new->fs_freq = fs->fs_freq;
	return (new);
}