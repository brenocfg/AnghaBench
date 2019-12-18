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
struct partition_metadata {int /*<<< orphan*/ * newfs; TYPE_1__* fstab; int /*<<< orphan*/ * name; } ;
struct fstab {int /*<<< orphan*/  fs_passno; int /*<<< orphan*/  fs_freq; int /*<<< orphan*/ * fs_type; int /*<<< orphan*/ * fs_mntops; int /*<<< orphan*/ * fs_vfstype; int /*<<< orphan*/ * fs_file; int /*<<< orphan*/ * fs_spec; } ;
struct TYPE_2__ {int /*<<< orphan*/  fs_passno; int /*<<< orphan*/  fs_freq; void* fs_type; void* fs_mntops; void* fs_vfstype; void* fs_file; void* fs_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct partition_metadata*,int /*<<< orphan*/ ) ; 
 struct partition_metadata* calloc (int,int) ; 
 struct fstab* getfsent () ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  metadata ; 
 int /*<<< orphan*/  part_metadata ; 
 int /*<<< orphan*/  setfsent () ; 
 void* strdup (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
init_fstab_metadata(void)
{
	struct fstab *fstab;
	struct partition_metadata *md;

	setfsent();
	while ((fstab = getfsent()) != NULL) {
		md = calloc(1, sizeof(struct partition_metadata));

		md->name = NULL;
		if (strncmp(fstab->fs_spec, "/dev/", 5) == 0)
			md->name = strdup(&fstab->fs_spec[5]);

		md->fstab = malloc(sizeof(struct fstab));
		md->fstab->fs_spec = strdup(fstab->fs_spec);
		md->fstab->fs_file = strdup(fstab->fs_file);
		md->fstab->fs_vfstype = strdup(fstab->fs_vfstype);
		md->fstab->fs_mntops = strdup(fstab->fs_mntops);
		md->fstab->fs_type = strdup(fstab->fs_type);
		md->fstab->fs_freq = fstab->fs_freq;
		md->fstab->fs_passno = fstab->fs_passno;

		md->newfs = NULL;
		
		TAILQ_INSERT_TAIL(&part_metadata, md, metadata);
	}
}