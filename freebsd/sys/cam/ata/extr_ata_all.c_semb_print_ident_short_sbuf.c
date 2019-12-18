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
struct sep_identify_data {int /*<<< orphan*/  firmware_rev; int /*<<< orphan*/  product_rev; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_strvis_sbuf (struct sbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*) ; 

void
semb_print_ident_short_sbuf(struct sep_identify_data *ident_data, struct sbuf *sb)
{

	sbuf_printf(sb, "<");
	cam_strvis_sbuf(sb, ident_data->vendor_id, 8, 0);
	sbuf_printf(sb, " ");
	cam_strvis_sbuf(sb, ident_data->product_id, 16, 0);
	sbuf_printf(sb, " ");
	cam_strvis_sbuf(sb, ident_data->product_rev, 4, 0);
	sbuf_printf(sb, " ");
	cam_strvis_sbuf(sb, ident_data->firmware_rev, 4, 0);
	sbuf_printf(sb, ">");
}