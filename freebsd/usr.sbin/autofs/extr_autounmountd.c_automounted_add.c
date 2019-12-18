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
struct automounted_fs {int /*<<< orphan*/  af_mountpoint; int /*<<< orphan*/  af_fsid; int /*<<< orphan*/  af_mount_time; } ;
typedef  int /*<<< orphan*/  fsid_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct automounted_fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_next ; 
 int /*<<< orphan*/  automounted ; 
 struct automounted_fs* calloc (int,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct automounted_fs *
automounted_add(fsid_t fsid, const char *mountpoint)
{
	struct automounted_fs *af;

	af = calloc(1, sizeof(*af));
	if (af == NULL)
		log_err(1, "calloc");
	af->af_mount_time = time(NULL);
	af->af_fsid = fsid;
	strlcpy(af->af_mountpoint, mountpoint, sizeof(af->af_mountpoint));

	TAILQ_INSERT_TAIL(&automounted, af, af_next);

	return (af);
}