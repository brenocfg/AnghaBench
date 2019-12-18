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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_transportid_header {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  scsi_transportid_sbuf (struct sbuf*,struct scsi_transportid_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
persist_print_transportid(uint8_t *buf, uint32_t len)
{
	struct sbuf *sb;

	sb = sbuf_new_auto();
	if (sb == NULL)
		fprintf(stderr, "Unable to allocate sbuf\n");

	scsi_transportid_sbuf(sb, (struct scsi_transportid_header *)buf, len);

	sbuf_finish(sb);

	fprintf(stdout, "%s\n", sbuf_data(sb));

	sbuf_delete(sb);
}