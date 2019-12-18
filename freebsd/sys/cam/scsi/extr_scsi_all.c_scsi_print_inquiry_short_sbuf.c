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
struct scsi_inquiry_data {int /*<<< orphan*/  revision; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_strvis_sbuf (struct sbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*) ; 

void
scsi_print_inquiry_short_sbuf(struct sbuf *sb, struct scsi_inquiry_data *inq_data)
{

	sbuf_printf(sb, "<");
	cam_strvis_sbuf(sb, inq_data->vendor, sizeof(inq_data->vendor), 0);
	sbuf_printf(sb, " ");
	cam_strvis_sbuf(sb, inq_data->product, sizeof(inq_data->product), 0);
	sbuf_printf(sb, " ");
	cam_strvis_sbuf(sb, inq_data->revision, sizeof(inq_data->revision), 0);
	sbuf_printf(sb, "> ");
}