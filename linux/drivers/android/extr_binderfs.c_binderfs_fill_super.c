#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_time_gran; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_user_ns; struct binderfs_info* s_fs_info; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_iflags; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_ino; } ;
struct TYPE_6__ {scalar_t__ stats_mode; } ;
struct binderfs_info {TYPE_3__ mount_opts; int /*<<< orphan*/  root_uid; int /*<<< orphan*/  root_gid; int /*<<< orphan*/  ipc_ns; } ;
struct binderfs_device {int /*<<< orphan*/  name; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {TYPE_1__* nsproxy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ipc_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDERFS_SUPER_MAGIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIRST_INODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SB_I_NODEV ; 
 int /*<<< orphan*/  SB_I_NOEXEC ; 
 scalar_t__ STATS_GLOBAL ; 
 int S_IFDIR ; 
 char* binder_devices_param ; 
 int binderfs_binder_ctl_create (struct super_block*) ; 
 int binderfs_binder_device_create (struct inode*,int /*<<< orphan*/ *,struct binderfs_device*) ; 
 int /*<<< orphan*/  binderfs_dir_inode_operations ; 
 int binderfs_parse_mount_opts (void*,TYPE_3__*) ; 
 int /*<<< orphan*/  binderfs_super_ops ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  get_ipc_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int init_binder_logs (struct super_block*) ; 
 struct binderfs_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int binderfs_fill_super(struct super_block *sb, void *data, int silent)
{
	int ret;
	struct binderfs_info *info;
	struct inode *inode = NULL;
	struct binderfs_device device_info = { 0 };
	const char *name;
	size_t len;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;

	/*
	 * The binderfs filesystem can be mounted by userns root in a
	 * non-initial userns. By default such mounts have the SB_I_NODEV flag
	 * set in s_iflags to prevent security issues where userns root can
	 * just create random device nodes via mknod() since it owns the
	 * filesystem mount. But binderfs does not allow to create any files
	 * including devices nodes. The only way to create binder devices nodes
	 * is through the binder-control device which userns root is explicitly
	 * allowed to do. So removing the SB_I_NODEV flag from s_iflags is both
	 * necessary and safe.
	 */
	sb->s_iflags &= ~SB_I_NODEV;
	sb->s_iflags |= SB_I_NOEXEC;
	sb->s_magic = BINDERFS_SUPER_MAGIC;
	sb->s_op = &binderfs_super_ops;
	sb->s_time_gran = 1;

	sb->s_fs_info = kzalloc(sizeof(struct binderfs_info), GFP_KERNEL);
	if (!sb->s_fs_info)
		return -ENOMEM;
	info = sb->s_fs_info;

	info->ipc_ns = get_ipc_ns(current->nsproxy->ipc_ns);

	ret = binderfs_parse_mount_opts(data, &info->mount_opts);
	if (ret)
		return ret;

	info->root_gid = make_kgid(sb->s_user_ns, 0);
	if (!gid_valid(info->root_gid))
		info->root_gid = GLOBAL_ROOT_GID;
	info->root_uid = make_kuid(sb->s_user_ns, 0);
	if (!uid_valid(info->root_uid))
		info->root_uid = GLOBAL_ROOT_UID;

	inode = new_inode(sb);
	if (!inode)
		return -ENOMEM;

	inode->i_ino = FIRST_INODE;
	inode->i_fop = &simple_dir_operations;
	inode->i_mode = S_IFDIR | 0755;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_op = &binderfs_dir_inode_operations;
	set_nlink(inode, 2);

	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
		return -ENOMEM;

	ret = binderfs_binder_ctl_create(sb);
	if (ret)
		return ret;

	name = binder_devices_param;
	for (len = strcspn(name, ","); len > 0; len = strcspn(name, ",")) {
		strscpy(device_info.name, name, len + 1);
		ret = binderfs_binder_device_create(inode, NULL, &device_info);
		if (ret)
			return ret;
		name += len;
		if (*name == ',')
			name++;
	}

	if (info->mount_opts.stats_mode == STATS_GLOBAL)
		return init_binder_logs(sb);

	return 0;
}