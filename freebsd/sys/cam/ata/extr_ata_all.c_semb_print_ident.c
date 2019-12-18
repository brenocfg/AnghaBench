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
struct sep_identify_data {int /*<<< orphan*/  interface_rev; int /*<<< orphan*/  interface_id; } ;
typedef  int /*<<< orphan*/  ins ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  cam_strvis (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  semb_print_ident_short (struct sep_identify_data*) ; 

void
semb_print_ident(struct sep_identify_data *ident_data)
{
	char in[7], ins[5];

	semb_print_ident_short(ident_data);
	cam_strvis(in, ident_data->interface_id, 6, sizeof(in));
	cam_strvis(ins, ident_data->interface_rev, 4, sizeof(ins));
	printf(" SEMB %s %s device\n", in, ins);
}