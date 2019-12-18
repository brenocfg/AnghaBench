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
struct gas_dialog_info {int /*<<< orphan*/  sd_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memset (struct gas_dialog_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void gas_serv_dialog_clear(struct gas_dialog_info *dia)
{
	wpabuf_free(dia->sd_resp);
	os_memset(dia, 0, sizeof(*dia));
}