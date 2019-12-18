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
struct stat {int /*<<< orphan*/  st_size; } ;
struct mlx5_tool_addr {int dummy; } ;
struct mlx5_fw_update {scalar_t__ img_fw_data; int /*<<< orphan*/  img_fw_data_len; int /*<<< orphan*/  devaddr; } ;
typedef  int /*<<< orphan*/  fwup ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  MLX5_FW_UPDATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int fstat (int,struct stat*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mlx5_fw_update*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlx5_tool_addr const*,int) ; 
 int /*<<< orphan*/  memset (struct mlx5_fw_update*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int
mlx5tool_fw_update(int ctldev, const struct mlx5_tool_addr *addr,
    const char *img_fw_path)
{
	struct stat st;
	struct mlx5_fw_update fwup;
	int error, fd, res;

	res = 0;
	fd = open(img_fw_path, O_RDONLY);
	if (fd == -1) {
		warn("Unable to open %s", img_fw_path);
		res = 1;
		goto close_fd;
	}
	error = fstat(fd, &st);
	if (error != 0) {
		warn("Unable to stat %s", img_fw_path);
		res = 1;
		goto close_fd;
	}
	memset(&fwup, 0, sizeof(fwup));
	memcpy(&fwup.devaddr, addr, sizeof(fwup.devaddr));
	fwup.img_fw_data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE,
	    fd, 0);
	if (fwup.img_fw_data == MAP_FAILED) {
		warn("Unable to mmap %s", img_fw_path);
		res = 1;
		goto close_fd;
	}
	fwup.img_fw_data_len = st.st_size;

	error = ioctl(ctldev, MLX5_FW_UPDATE, &fwup);
	if (error == -1) {
		warn("MLX5_FW_UPDATE");
	}

	munmap(fwup.img_fw_data, st.st_size);
close_fd:
	close(fd);
	return (res);
}