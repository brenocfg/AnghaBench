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
typedef  int /*<<< orphan*/  txt ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const char * algo_agility_txt(const u8 *algo_agility)
{
	static char txt[4 * 2 + 1];

	wpa_snprintf_hex(txt, sizeof(txt), algo_agility, 4);
	return txt;
}