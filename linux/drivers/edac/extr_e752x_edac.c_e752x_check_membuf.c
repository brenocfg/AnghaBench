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
typedef  int u8 ;
struct e752x_error_info {int buf_ferr; int buf_nerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  membuf_error (int,int*,int) ; 

__attribute__((used)) static void e752x_check_membuf(struct e752x_error_info *info,
			int *error_found, int handle_error)
{
	u8 stat8;

	stat8 = info->buf_ferr;

	if (stat8 & 0x0f) {	/* Error, so process */
		stat8 &= 0x0f;
		membuf_error(stat8, error_found, handle_error);
	}

	stat8 = info->buf_nerr;

	if (stat8 & 0x0f) {	/* Error, so process */
		stat8 &= 0x0f;
		membuf_error(stat8, error_found, handle_error);
	}
}