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
struct sftp_statvfs {int f_files; int f_ffree; int f_blocks; int f_bfree; int f_frsize; int f_bavail; scalar_t__ f_favail; } ;
struct sftp_conn {int dummy; } ;
typedef  int /*<<< orphan*/  s_used ;
typedef  int /*<<< orphan*/  s_total ;
typedef  int /*<<< orphan*/  s_root ;
typedef  int /*<<< orphan*/  s_icapacity ;
typedef  int /*<<< orphan*/  s_dcapacity ;
typedef  int /*<<< orphan*/  s_avail ;

/* Variables and functions */
 int FMT_SCALED_STRSIZE ; 
 int do_statvfs (struct sftp_conn*,char const*,struct sftp_statvfs*,int) ; 
 int /*<<< orphan*/  fmt_scaled (int,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
do_df(struct sftp_conn *conn, const char *path, int hflag, int iflag)
{
	struct sftp_statvfs st;
	char s_used[FMT_SCALED_STRSIZE], s_avail[FMT_SCALED_STRSIZE];
	char s_root[FMT_SCALED_STRSIZE], s_total[FMT_SCALED_STRSIZE];
	char s_icapacity[16], s_dcapacity[16];

	if (do_statvfs(conn, path, &st, 1) == -1)
		return -1;
	if (st.f_files == 0)
		strlcpy(s_icapacity, "ERR", sizeof(s_icapacity));
	else {
		snprintf(s_icapacity, sizeof(s_icapacity), "%3llu%%",
		    (unsigned long long)(100 * (st.f_files - st.f_ffree) /
		    st.f_files));
	}
	if (st.f_blocks == 0)
		strlcpy(s_dcapacity, "ERR", sizeof(s_dcapacity));
	else {
		snprintf(s_dcapacity, sizeof(s_dcapacity), "%3llu%%",
		    (unsigned long long)(100 * (st.f_blocks - st.f_bfree) /
		    st.f_blocks));
	}
	if (iflag) {
		printf("     Inodes        Used       Avail      "
		    "(root)    %%Capacity\n");
		printf("%11llu %11llu %11llu %11llu         %s\n",
		    (unsigned long long)st.f_files,
		    (unsigned long long)(st.f_files - st.f_ffree),
		    (unsigned long long)st.f_favail,
		    (unsigned long long)st.f_ffree, s_icapacity);
	} else if (hflag) {
		strlcpy(s_used, "error", sizeof(s_used));
		strlcpy(s_avail, "error", sizeof(s_avail));
		strlcpy(s_root, "error", sizeof(s_root));
		strlcpy(s_total, "error", sizeof(s_total));
		fmt_scaled((st.f_blocks - st.f_bfree) * st.f_frsize, s_used);
		fmt_scaled(st.f_bavail * st.f_frsize, s_avail);
		fmt_scaled(st.f_bfree * st.f_frsize, s_root);
		fmt_scaled(st.f_blocks * st.f_frsize, s_total);
		printf("    Size     Used    Avail   (root)    %%Capacity\n");
		printf("%7sB %7sB %7sB %7sB         %s\n",
		    s_total, s_used, s_avail, s_root, s_dcapacity);
	} else {
		printf("        Size         Used        Avail       "
		    "(root)    %%Capacity\n");
		printf("%12llu %12llu %12llu %12llu         %s\n",
		    (unsigned long long)(st.f_frsize * st.f_blocks / 1024),
		    (unsigned long long)(st.f_frsize *
		    (st.f_blocks - st.f_bfree) / 1024),
		    (unsigned long long)(st.f_frsize * st.f_bavail / 1024),
		    (unsigned long long)(st.f_frsize * st.f_bfree / 1024),
		    s_dcapacity);
	}
	return 0;
}