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
typedef  int /*<<< orphan*/  u_char ;
struct gctl_req {int dummy; } ;
struct g_cache_metadata {scalar_t__ md_provsize; void* md_size; void* md_bsize; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; } ;
typedef  int /*<<< orphan*/  sector ;
typedef  void* intmax_t ;

/* Variables and functions */
 char const* G_CACHE_MAGIC ; 
 int /*<<< orphan*/  G_CACHE_VERSION ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cache_metadata_encode (struct g_cache_metadata*,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ g_get_mediasize (char const*) ; 
 int g_metadata_store (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 void* gctl_get_intmax (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
cache_label(struct gctl_req *req)
{
	struct g_cache_metadata md;
	u_char sector[512];
	const char *name;
	int error, nargs;
	intmax_t val;

	bzero(sector, sizeof(sector));
	nargs = gctl_get_int(req, "nargs");
	if (nargs != 2) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}

	strlcpy(md.md_magic, G_CACHE_MAGIC, sizeof(md.md_magic));
	md.md_version = G_CACHE_VERSION;
	name = gctl_get_ascii(req, "arg0");
	strlcpy(md.md_name, name, sizeof(md.md_name));
	val = gctl_get_intmax(req, "blocksize");
	md.md_bsize = val;
	val = gctl_get_intmax(req, "size");
	md.md_size = val;

	name = gctl_get_ascii(req, "arg1");
	md.md_provsize = g_get_mediasize(name);
	if (md.md_provsize == 0) {
		fprintf(stderr, "Can't get mediasize of %s: %s.\n",
		    name, strerror(errno));
		gctl_error(req, "Not fully done.");
		return;
	}
	cache_metadata_encode(&md, sector);
	error = g_metadata_store(name, sector, sizeof(sector));
	if (error != 0) {
		fprintf(stderr, "Can't store metadata on %s: %s.\n",
		    name, strerror(error));
		gctl_error(req, "Not fully done.");
		return;
	}
	if (verbose)
		printf("Metadata value stored on %s.\n", name);
}