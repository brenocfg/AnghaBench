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
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_putbuf (struct sbuf*) ; 
 int /*<<< orphan*/  scsi_print_inquiry_sbuf (struct sbuf*,struct scsi_inquiry_data*) ; 

void
scsi_print_inquiry(struct scsi_inquiry_data *inq_data)
{
	struct sbuf	sb;
	char		buffer[120];

	sbuf_new(&sb, buffer, 120, SBUF_FIXEDLEN);
	scsi_print_inquiry_sbuf(&sb, inq_data);
	sbuf_finish(&sb);
	sbuf_putbuf(&sb);
}