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
struct ata_params {int /*<<< orphan*/  revision; int /*<<< orphan*/  model; } ;
typedef  int /*<<< orphan*/  revision ;
typedef  int /*<<< orphan*/  product ;

/* Variables and functions */
 int /*<<< orphan*/  cam_strvis (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

void
ata_print_ident_short(struct ata_params *ident_data)
{
	char product[48], revision[16];

	cam_strvis(product, ident_data->model, sizeof(ident_data->model),
		   sizeof(product));
	cam_strvis(revision, ident_data->revision, sizeof(ident_data->revision),
		   sizeof(revision));
	printf("<%s %s>", product, revision);
}