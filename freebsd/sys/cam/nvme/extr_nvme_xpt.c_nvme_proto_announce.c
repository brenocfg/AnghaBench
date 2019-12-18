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
struct sbuf {int dummy; } ;
struct cam_ed {int /*<<< orphan*/  nvme_data; int /*<<< orphan*/  nvme_cdata; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  nvme_print_ident (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_putbuf (struct sbuf*) ; 

__attribute__((used)) static void
nvme_proto_announce(struct cam_ed *device)
{
	struct sbuf	sb;
	char		buffer[120];

	sbuf_new(&sb, buffer, sizeof(buffer), SBUF_FIXEDLEN);
	nvme_print_ident(device->nvme_cdata, device->nvme_data, &sb);
	sbuf_finish(&sb);
	sbuf_putbuf(&sb);
}