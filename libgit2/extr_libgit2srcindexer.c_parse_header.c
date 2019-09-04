#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct git_pack_header {scalar_t__ hdr_signature; int /*<<< orphan*/  hdr_version; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
struct git_pack_file {TYPE_1__ mwf; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ git_map ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INDEXER ; 
 int /*<<< orphan*/  GIT_MAP_SHARED ; 
 int /*<<< orphan*/  GIT_PROT_READ ; 
 int /*<<< orphan*/  PACK_SIGNATURE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (struct git_pack_header*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int p_mmap (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_munmap (TYPE_2__*) ; 
 int /*<<< orphan*/  pack_version_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_header(struct git_pack_header *hdr, struct git_pack_file *pack)
{
	int error;
	git_map map;

	if ((error = p_mmap(&map, sizeof(*hdr), GIT_PROT_READ, GIT_MAP_SHARED, pack->mwf.fd, 0)) < 0)
		return error;

	memcpy(hdr, map.data, sizeof(*hdr));
	p_munmap(&map);

	/* Verify we recognize this pack file format. */
	if (hdr->hdr_signature != ntohl(PACK_SIGNATURE)) {
		git_error_set(GIT_ERROR_INDEXER, "wrong pack signature");
		return -1;
	}

	if (!pack_version_ok(hdr->hdr_version)) {
		git_error_set(GIT_ERROR_INDEXER, "wrong pack version");
		return -1;
	}

	return 0;
}