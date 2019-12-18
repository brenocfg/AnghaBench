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
typedef  int u_char ;
struct cmsghdr {int cmsg_len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int* CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_gen_cmsg(FILE *fp, struct cmsghdr *cmsghdr)
{
	u_char *q;

	fputs("{", fp);
	for (q = CMSG_DATA(cmsghdr);
	     q < (u_char *)cmsghdr + cmsghdr->cmsg_len; q++) {
		fprintf(fp, "%s0x%02x", q == CMSG_DATA(cmsghdr) ? "" : ",", *q);
	}
	fputs("}", fp);
}