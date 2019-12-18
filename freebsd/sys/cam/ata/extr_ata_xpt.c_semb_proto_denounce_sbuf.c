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
struct sep_identify_data {int dummy; } ;
struct sbuf {int dummy; } ;
struct cam_ed {int /*<<< orphan*/  ident_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  semb_print_ident_short_sbuf (struct sep_identify_data*,struct sbuf*) ; 

__attribute__((used)) static void
semb_proto_denounce_sbuf(struct cam_ed *device, struct sbuf *sb)
{
	semb_print_ident_short_sbuf((struct sep_identify_data *)&device->ident_data, sb);
}