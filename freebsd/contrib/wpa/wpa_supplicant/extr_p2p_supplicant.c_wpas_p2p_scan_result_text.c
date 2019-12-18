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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int p2p_scan_result_text (int /*<<< orphan*/  const*,size_t,char*,char*) ; 

int wpas_p2p_scan_result_text(const u8 *ies, size_t ies_len, char *buf,
			      char *end)
{
	return p2p_scan_result_text(ies, ies_len, buf, end);
}