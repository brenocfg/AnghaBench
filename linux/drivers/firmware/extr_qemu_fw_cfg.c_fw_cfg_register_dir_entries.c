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
typedef  int u32 ;
struct fw_cfg_file {int dummy; } ;
typedef  int /*<<< orphan*/  files_count ;
typedef  struct fw_cfg_file __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FW_CFG_FILE_DIR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int be32_to_cpu (struct fw_cfg_file) ; 
 int fw_cfg_read_blob (int /*<<< orphan*/ ,struct fw_cfg_file*,int,size_t) ; 
 int fw_cfg_register_file (struct fw_cfg_file*) ; 
 int /*<<< orphan*/  kfree (struct fw_cfg_file*) ; 
 struct fw_cfg_file* kmalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fw_cfg_register_dir_entries(void)
{
	int ret = 0;
	__be32 files_count;
	u32 count, i;
	struct fw_cfg_file *dir;
	size_t dir_size;

	ret = fw_cfg_read_blob(FW_CFG_FILE_DIR, &files_count,
			0, sizeof(files_count));
	if (ret < 0)
		return ret;

	count = be32_to_cpu(files_count);
	dir_size = count * sizeof(struct fw_cfg_file);

	dir = kmalloc(dir_size, GFP_KERNEL);
	if (!dir)
		return -ENOMEM;

	ret = fw_cfg_read_blob(FW_CFG_FILE_DIR, dir,
			sizeof(files_count), dir_size);
	if (ret < 0)
		goto end;

	for (i = 0; i < count; i++) {
		ret = fw_cfg_register_file(&dir[i]);
		if (ret)
			break;
	}

end:
	kfree(dir);
	return ret;
}