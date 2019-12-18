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
struct msghdr {scalar_t__ msg_controllen; char* msg_control; } ;
struct cmsghdr {int cmsg_level; int cmsg_type; scalar_t__ cmsg_len; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
#define  IPPROTO_SCTP 128 
 char* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_struct (int /*<<< orphan*/ ,uintptr_t,char*,scalar_t__) ; 
 int /*<<< orphan*/  print_gen_cmsg (int /*<<< orphan*/ *,struct cmsghdr*) ; 
 int /*<<< orphan*/  print_integer_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_pointer (int /*<<< orphan*/ *,uintptr_t) ; 
 int /*<<< orphan*/  print_sctp_cmsg (int /*<<< orphan*/ *,int,struct cmsghdr*) ; 
 char* sysdecode_cmsg_type (int,int) ; 
 int /*<<< orphan*/  sysdecode_sockopt_level ; 

__attribute__((used)) static void
print_cmsgs(FILE *fp, pid_t pid, bool receive, struct msghdr *msghdr)
{
	struct cmsghdr *cmsghdr;
	char *cmsgbuf;
	const char *temp;
	socklen_t len;
	int level, type;
	bool first;

	len = msghdr->msg_controllen;
	if (len == 0) {
		fputs("{}", fp);
		return;
	}
	cmsgbuf = calloc(1, len);
	if (get_struct(pid, (uintptr_t)msghdr->msg_control, cmsgbuf, len) == -1) {
		print_pointer(fp, (uintptr_t)msghdr->msg_control);
		free(cmsgbuf);
		return;
	}
	msghdr->msg_control = cmsgbuf;
	first = true;
	fputs("{", fp);
	for (cmsghdr = CMSG_FIRSTHDR(msghdr);
	   cmsghdr != NULL;
	   cmsghdr = CMSG_NXTHDR(msghdr, cmsghdr)) {
		level = cmsghdr->cmsg_level;
		type = cmsghdr->cmsg_type;
		len = cmsghdr->cmsg_len;
		fprintf(fp, "%s{level=", first ? "" : ",");
		print_integer_arg(sysdecode_sockopt_level, fp, level);
		fputs(",type=", fp);
		temp = sysdecode_cmsg_type(level, type);
		if (temp) {
			fputs(temp, fp);
		} else {
			fprintf(fp, "%d", type);
		}
		fputs(",data=", fp);
		switch (level) {
		case IPPROTO_SCTP:
			print_sctp_cmsg(fp, receive, cmsghdr);
			break;
		default:
			print_gen_cmsg(fp, cmsghdr);
			break;
		}
		fputs("}", fp);
		first = false;
	}
	fputs("}", fp);
	free(cmsgbuf);
}