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
struct ieee802_1x_kay {int co; } ;
typedef  enum confidentiality_offset { ____Placeholder_confidentiality_offset } confidentiality_offset ;

/* Variables and functions */

int secy_cp_control_confidentiality_offset(struct ieee802_1x_kay *kay,
					   enum confidentiality_offset co)
{
	kay->co = co;
	return 0;
}