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
struct sftp_conn {int dummy; } ;
typedef  int /*<<< orphan*/  Attrib ;

/* Variables and functions */
 char* do_realpath (struct sftp_conn*,char const*) ; 
 int download_dir_internal (struct sftp_conn*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 

int
download_dir(struct sftp_conn *conn, const char *src, const char *dst,
    Attrib *dirattrib, int preserve_flag, int print_flag, int resume_flag,
    int fsync_flag)
{
	char *src_canon;
	int ret;

	if ((src_canon = do_realpath(conn, src)) == NULL) {
		error("Unable to canonicalize path \"%s\"", src);
		return -1;
	}

	ret = download_dir_internal(conn, src_canon, dst, 0,
	    dirattrib, preserve_flag, print_flag, resume_flag, fsync_flag);
	free(src_canon);
	return ret;
}