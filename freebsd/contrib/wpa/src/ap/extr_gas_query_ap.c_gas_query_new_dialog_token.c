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
struct gas_query_ap {int dummy; } ;

/* Variables and functions */
 scalar_t__ gas_query_dialog_token_available (struct gas_query_ap*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int gas_query_new_dialog_token(struct gas_query_ap *gas, const u8 *dst)
{
	static int next_start = 0;
	int dialog_token;

	for (dialog_token = 0; dialog_token < 256; dialog_token++) {
		if (gas_query_dialog_token_available(
			    gas, dst, (next_start + dialog_token) % 256))
			break;
	}
	if (dialog_token == 256)
		return -1; /* Too many pending queries */
	dialog_token = (next_start + dialog_token) % 256;
	next_start = (dialog_token + 1) % 256;
	return dialog_token;
}