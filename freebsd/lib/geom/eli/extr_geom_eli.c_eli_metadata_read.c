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
struct g_eli_metadata {scalar_t__ md_version; } ;
typedef  int /*<<< orphan*/  sector ;

/* Variables and functions */
#define  EINVAL 129 
#define  EOPNOTSUPP 128 
 int /*<<< orphan*/  G_ELI_MAGIC ; 
 int /*<<< orphan*/  G_ELI_VERSION ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int eli_metadata_decode (unsigned char*,struct g_eli_metadata*) ; 
 int errno ; 
 scalar_t__ g_get_sectorsize (char const*) ; 
 int g_metadata_read (char const*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,char const*,...) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int
eli_metadata_read(struct gctl_req *req, const char *prov,
    struct g_eli_metadata *md)
{
	unsigned char sector[sizeof(struct g_eli_metadata)];
	int error;

	if (g_get_sectorsize(prov) == 0) {
		int fd;

		/* This is a file probably. */
		fd = open(prov, O_RDONLY);
		if (fd == -1) {
			gctl_error(req, "Cannot open %s: %s.", prov,
			    strerror(errno));
			return (-1);
		}
		if (read(fd, sector, sizeof(sector)) != sizeof(sector)) {
			gctl_error(req, "Cannot read metadata from %s: %s.",
			    prov, strerror(errno));
			close(fd);
			return (-1);
		}
		close(fd);
	} else {
		/* This is a GEOM provider. */
		error = g_metadata_read(prov, sector, sizeof(sector),
		    G_ELI_MAGIC);
		if (error != 0) {
			gctl_error(req, "Cannot read metadata from %s: %s.",
			    prov, strerror(error));
			return (-1);
		}
	}
	error = eli_metadata_decode(sector, md);
	switch (error) {
	case 0:
		break;
	case EOPNOTSUPP:
		gctl_error(req,
		    "Provider's %s metadata version %u is too new.\n"
		    "geli: The highest supported version is %u.",
		    prov, (unsigned int)md->md_version, G_ELI_VERSION);
		return (-1);
	case EINVAL:
		gctl_error(req, "Inconsistent provider's %s metadata.", prov);
		return (-1);
	default:
		gctl_error(req,
		    "Unexpected error while decoding provider's %s metadata: %s.",
		    prov, strerror(error));
		return (-1);
	}
	return (0);
}