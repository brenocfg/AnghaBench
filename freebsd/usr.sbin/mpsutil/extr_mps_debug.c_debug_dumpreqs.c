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
typedef  int /*<<< orphan*/  sysctlbuf ;
struct mps_dumpreq_hdr {int numframes; int smid; int state; int deschi; int desclo; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t MPS_FRAME_LEN ; 
 int /*<<< orphan*/  errno ; 
 int find_sgl (char*) ; 
 scalar_t__ is_mps ; 
 char* malloc (size_t) ; 
 int mps_unit ; 
 int /*<<< orphan*/  print_sgl (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
debug_dumpreqs(int ac, char **av)
{
	struct mps_dumpreq_hdr *hdr;
	char *buf, sysctlbuf[128];
	size_t len;
	int numframes, error, offset;

	len = 0;
	buf = NULL;
	snprintf(sysctlbuf, sizeof(sysctlbuf), "dev.%s.%d.dump_reqs",
	    is_mps ? "mps" : "mpr", mps_unit);

	error = sysctlbyname(sysctlbuf, NULL, &len, NULL, 0);
	if (error)
		return (error);

	if (len == 0)
		return (0);

	buf = malloc(len);
	if (buf == NULL)
		return (ENOMEM);

	error = sysctlbyname(sysctlbuf, buf, &len, NULL, 0);
	if (error) {
		printf("len= %zd, error= %d errno= %d\n", len, error, errno);
		return (error);
	}

	while (len >= MPS_FRAME_LEN) {
		hdr = (struct mps_dumpreq_hdr *)buf;
		numframes = hdr->numframes;

		printf("SMID= %d state= %#x numframes= %d desc.hi= %#08x "
		    "desc.lo= %#08x\n", hdr->smid, hdr->state,
		    hdr->numframes, hdr->deschi, hdr->desclo);

		buf += sizeof(struct mps_dumpreq_hdr);
		len -= sizeof(struct mps_dumpreq_hdr);

		if ((offset = find_sgl(buf)) != -1)
			print_sgl(buf, offset, numframes);

		buf += MPS_FRAME_LEN * numframes;
		len -= MPS_FRAME_LEN * numframes;
	}

	return (error);
}