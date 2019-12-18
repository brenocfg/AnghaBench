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
struct TYPE_5__ {int common; int ofs_delta; int multi_ack_detailed; int multi_ack; int include_tag; int side_band_64k; int side_band; int delete_refs; int thin_pack; } ;
typedef  TYPE_1__ transport_smart_caps ;
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_6__ {char* capabilities; } ;
typedef  TYPE_2__ git_pkt_ref ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CAP_DELETE_REFS ; 
 int /*<<< orphan*/  GIT_CAP_INCLUDE_TAG ; 
 int /*<<< orphan*/  GIT_CAP_MULTI_ACK ; 
 int /*<<< orphan*/  GIT_CAP_MULTI_ACK_DETAILED ; 
 int /*<<< orphan*/  GIT_CAP_OFS_DELTA ; 
 int /*<<< orphan*/  GIT_CAP_SIDE_BAND ; 
 int /*<<< orphan*/  GIT_CAP_SIDE_BAND_64K ; 
 int /*<<< orphan*/  GIT_CAP_SYMREF ; 
 int /*<<< orphan*/  GIT_CAP_THIN_PACK ; 
 int GIT_ENOTFOUND ; 
 int append_symref (char const**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_smart__ofs_delta_enabled ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int git_smart__detect_caps(git_pkt_ref *pkt, transport_smart_caps *caps, git_vector *symrefs)
{
	const char *ptr;

	/* No refs or capabilites, odd but not a problem */
	if (pkt == NULL || pkt->capabilities == NULL)
		return GIT_ENOTFOUND;

	ptr = pkt->capabilities;
	while (ptr != NULL && *ptr != '\0') {
		if (*ptr == ' ')
			ptr++;

		if (git_smart__ofs_delta_enabled && !git__prefixcmp(ptr, GIT_CAP_OFS_DELTA)) {
			caps->common = caps->ofs_delta = 1;
			ptr += strlen(GIT_CAP_OFS_DELTA);
			continue;
		}

		/* Keep multi_ack_detailed before multi_ack */
		if (!git__prefixcmp(ptr, GIT_CAP_MULTI_ACK_DETAILED)) {
			caps->common = caps->multi_ack_detailed = 1;
			ptr += strlen(GIT_CAP_MULTI_ACK_DETAILED);
			continue;
		}

		if (!git__prefixcmp(ptr, GIT_CAP_MULTI_ACK)) {
			caps->common = caps->multi_ack = 1;
			ptr += strlen(GIT_CAP_MULTI_ACK);
			continue;
		}

		if (!git__prefixcmp(ptr, GIT_CAP_INCLUDE_TAG)) {
			caps->common = caps->include_tag = 1;
			ptr += strlen(GIT_CAP_INCLUDE_TAG);
			continue;
		}

		/* Keep side-band check after side-band-64k */
		if (!git__prefixcmp(ptr, GIT_CAP_SIDE_BAND_64K)) {
			caps->common = caps->side_band_64k = 1;
			ptr += strlen(GIT_CAP_SIDE_BAND_64K);
			continue;
		}

		if (!git__prefixcmp(ptr, GIT_CAP_SIDE_BAND)) {
			caps->common = caps->side_band = 1;
			ptr += strlen(GIT_CAP_SIDE_BAND);
			continue;
		}

		if (!git__prefixcmp(ptr, GIT_CAP_DELETE_REFS)) {
			caps->common = caps->delete_refs = 1;
			ptr += strlen(GIT_CAP_DELETE_REFS);
			continue;
		}

		if (!git__prefixcmp(ptr, GIT_CAP_THIN_PACK)) {
			caps->common = caps->thin_pack = 1;
			ptr += strlen(GIT_CAP_THIN_PACK);
			continue;
		}

		if (!git__prefixcmp(ptr, GIT_CAP_SYMREF)) {
			int error;

			if ((error = append_symref(&ptr, symrefs, ptr)) < 0)
				return error;

			continue;
		}

		/* We don't know this capability, so skip it */
		ptr = strchr(ptr, ' ');
	}

	return 0;
}