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
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  pdinfo_t ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  boot_parse_cmdline (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * efiblk_get_pdinfo_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  set_currdev_pdinfo (int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

void
parse_loader_efi_config(EFI_HANDLE h, const char *env_fn)
{
	pdinfo_t *dp;
	struct stat st;
	int fd = -1;
	char *env = NULL;

	dp = efiblk_get_pdinfo_by_handle(h);
	if (dp == NULL)
		return;
	set_currdev_pdinfo(dp);
	if (stat(env_fn, &st) != 0)
		return;
	fd = open(env_fn, O_RDONLY);
	if (fd == -1)
		return;
	env = malloc(st.st_size + 1);
	if (env == NULL)
		goto out;
	if (read(fd, env, st.st_size) != st.st_size)
		goto out;
	env[st.st_size] = '\0';
	boot_parse_cmdline(env);
out:
	free(env);
	close(fd);
}