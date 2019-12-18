#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  desc; void* seg_size; void* seg_num; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_1__ qls_mpid_seg_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q81_MPID_COOKIE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qls_mpid_seg_hdr(qls_mpid_seg_hdr_t *seg_hdr, uint32_t seg_num,
	uint32_t seg_size, unsigned char *desc)
{
	memset(seg_hdr, 0, sizeof(qls_mpid_seg_hdr_t));

	seg_hdr->cookie = Q81_MPID_COOKIE;
	seg_hdr->seg_num = seg_num;
	seg_hdr->seg_size = seg_size;

	memcpy(seg_hdr->desc, desc, (sizeof(seg_hdr->desc))-1);

	return;
}