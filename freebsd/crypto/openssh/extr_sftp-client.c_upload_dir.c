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

/* Variables and functions */
 char* do_realpath (struct sftp_conn*,char const*) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int upload_dir_internal (struct sftp_conn*,char const*,char*,int /*<<< orphan*/ ,int,int,int,int) ; 

int
upload_dir(struct sftp_conn *conn, const char *src, const char *dst,
    int preserve_flag, int print_flag, int resume, int fsync_flag)
{
	char *dst_canon;
	int ret;

	if ((dst_canon = do_realpath(conn, dst)) == NULL) {
		error("Unable to canonicalize path \"%s\"", dst);
		return -1;
	}

	ret = upload_dir_internal(conn, src, dst_canon, 0, preserve_flag,
	    print_flag, resume, fsync_flag);

	free(dst_canon);
	return ret;
}