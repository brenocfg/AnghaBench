#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char* uintmax_t ;
struct stat {int st_uid; int st_gid; } ;
struct TYPE_3__ {scalar_t__ kf_file_size; int /*<<< orphan*/  kf_file_mode; } ;
struct TYPE_4__ {TYPE_1__ kf_file; } ;
struct kinfo_file {scalar_t__ kf_structsize; char* kf_path; TYPE_2__ kf_un; } ;
typedef  int /*<<< orphan*/  sizebuf ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int /*<<< orphan*/  HN_NOSPACE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 int getopt (int,char**,char*) ; 
 char* group_from_gid (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  humanize_number (char*,int,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* listmib ; 
 char* malloc (size_t) ; 
 size_t nitems (int*) ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  shm_decode_mode (int /*<<< orphan*/ ,char*) ; 
 int shm_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysctl (int*,size_t,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysctlnametomib (char*,int*,size_t*) ; 
 int /*<<< orphan*/  usage () ; 
 char* user_from_uid (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int
list_shm(int argc, char **argv)
{
	char *buf, *bp, sizebuf[8], str[10];
	const struct kinfo_file *kif;
	struct stat st;
	int c, error, fd, mib[3], ret;
	size_t len, miblen;
	bool hsize, uname;

	hsize = false;
	uname = true;

	while ((c = getopt(argc, argv, "hn")) != -1) {
		switch (c) {
		case 'h':
			hsize = true;
			break;
		case 'n':
			uname = false;
			break;
		default:
			usage();
			return (2);
		}
	}
	if (argc != optind) {
		usage();
		return (2);
	}

	miblen = nitems(mib);
	error = sysctlnametomib(listmib, mib, &miblen);
	if (error == -1) {
		warn("cannot translate %s", listmib);
		return (1);
	}
	len = 0;
	error = sysctl(mib, miblen, NULL, &len, NULL, 0);
	if (error == -1) {
		warn("cannot get %s length", listmib);
		return (1);
	}
	len = len * 4 / 3;
	buf = malloc(len);
	if (buf == NULL) {
		warn("malloc");
		return (1);
	}
	error = sysctl(mib, miblen, buf, &len, NULL, 0);
	if (error != 0) {
		warn("reading %s", listmib);
		ret = 1;
		goto out;
	}
	ret = 0;
	printf("MODE    \tOWNER\tGROUP\tSIZE\tPATH\n");
	for (bp = buf; bp < buf + len; bp += kif->kf_structsize) {
		kif = (const struct kinfo_file *)(void *)bp;
		if (kif->kf_structsize == 0)
			break;
		fd = shm_open(kif->kf_path, O_RDONLY, 0);
		if (fd == -1) {
			warn("open %s", kif->kf_path);
			ret = 1;
			continue;
		}
		error = fstat(fd, &st);
		close(fd);
		if (error != 0) {
			warn("stat %s", kif->kf_path);
			ret = 1;
			continue;
		}
		shm_decode_mode(kif->kf_un.kf_file.kf_file_mode, str);
		printf("%s\t", str);
		if (uname) {
			printf("%s\t%s\t", user_from_uid(st.st_uid, 0),
			    group_from_gid(st.st_gid, 0));
		} else {
			printf("%d\t%d\t", st.st_uid, st.st_gid);
		}
		if (hsize) {
			humanize_number(sizebuf, sizeof(sizebuf),
			    kif->kf_un.kf_file.kf_file_size, "", HN_AUTOSCALE,
			    HN_NOSPACE);
			printf("%s\t", sizebuf);
		} else {
			printf("%jd\t",
			    (uintmax_t)kif->kf_un.kf_file.kf_file_size);
		}
		printf("%s\n", kif->kf_path);
	}
out:
	free(buf);
	return (ret);
}