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
struct eap_fast_read_ctx {scalar_t__ f; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_fast_deinit_pac_data(struct eap_fast_read_ctx *rc)
{
	os_free(rc->buf);
	if (rc->f)
		fclose(rc->f);
}