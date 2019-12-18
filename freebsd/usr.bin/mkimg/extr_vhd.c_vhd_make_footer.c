#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  cylinders; } ;
struct vhd_footer {int /*<<< orphan*/  checksum; int /*<<< orphan*/  id; int /*<<< orphan*/  disk_type; TYPE_1__ geometry; int /*<<< orphan*/  current_size; int /*<<< orphan*/  original_size; int /*<<< orphan*/  creator_os; int /*<<< orphan*/  creator_version; int /*<<< orphan*/  creator_tool; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  version; int /*<<< orphan*/  features; int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  mkimg_uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  VHD_CREATOR_OS ; 
 int /*<<< orphan*/  VHD_CREATOR_TOOL ; 
 int /*<<< orphan*/  VHD_CREATOR_VERSION ; 
 int /*<<< orphan*/  VHD_FEATURES_RESERVED ; 
 int /*<<< orphan*/  VHD_FOOTER_COOKIE ; 
 int /*<<< orphan*/  VHD_VERSION ; 
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct vhd_footer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mkimg_uuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mkimg_uuid_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhd_checksum (struct vhd_footer*,int) ; 
 int /*<<< orphan*/  vhd_geometry (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vhd_timestamp () ; 

__attribute__((used)) static void
vhd_make_footer(struct vhd_footer *footer, uint64_t image_size,
    uint32_t disk_type, uint64_t data_offset)
{
	mkimg_uuid_t id;

	memset(footer, 0, sizeof(*footer));
	be64enc(&footer->cookie, VHD_FOOTER_COOKIE);
	be32enc(&footer->features, VHD_FEATURES_RESERVED);
	be32enc(&footer->version, VHD_VERSION);
	be64enc(&footer->data_offset, data_offset);
	be32enc(&footer->timestamp, vhd_timestamp());
	be32enc(&footer->creator_tool, VHD_CREATOR_TOOL);
	be32enc(&footer->creator_version, VHD_CREATOR_VERSION);
	be32enc(&footer->creator_os, VHD_CREATOR_OS);
	be64enc(&footer->original_size, image_size);
	be64enc(&footer->current_size, image_size);
	vhd_geometry(image_size, &footer->geometry);
	be16enc(&footer->geometry.cylinders, footer->geometry.cylinders);
	be32enc(&footer->disk_type, disk_type);
	mkimg_uuid(&id);
	mkimg_uuid_enc(&footer->id, &id);
	be32enc(&footer->checksum, vhd_checksum(footer, sizeof(*footer)));
}