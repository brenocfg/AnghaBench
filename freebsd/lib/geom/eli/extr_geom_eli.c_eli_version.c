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
struct gctl_req {int dummy; } ;
struct g_eli_metadata {int /*<<< orphan*/  md_version; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  md ;
typedef  int /*<<< orphan*/  kernver ;

/* Variables and functions */
 int /*<<< orphan*/  G_ELI_MAGIC ; 
 int G_ELI_VERSION ; 
 int g_metadata_read (char const*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,int) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 unsigned int le32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int sysctlbyname (char*,unsigned int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static void
eli_version(struct gctl_req *req)
{
	struct g_eli_metadata md;
	const char *name;
	unsigned int eli_version;
	int error, i, nargs;

	nargs = gctl_get_int(req, "nargs");

	if (nargs == 0) {
		unsigned int kernver;
		ssize_t size;

		size = sizeof(kernver);
		if (sysctlbyname("kern.geom.eli.version", &kernver, &size,
		    NULL, 0) == -1) {
			warn("Unable to obtain GELI kernel version");
		} else {
			printf("kernel: %u\n", kernver);
		}
		printf("userland: %u\n", G_ELI_VERSION);
		return;
	}

	for (i = 0; i < nargs; i++) {
		name = gctl_get_ascii(req, "arg%d", i);
		error = g_metadata_read(name, (unsigned char *)&md,
		    sizeof(md), G_ELI_MAGIC);
		if (error != 0) {
			warn("%s: Unable to read metadata: %s.", name,
			    strerror(error));
			gctl_error(req, "Not fully done.");
			continue;
		}
		eli_version = le32dec(&md.md_version);
		printf("%s: %u\n", name, eli_version);
	}
}