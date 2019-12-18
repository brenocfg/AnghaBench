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
struct anqp_query_info {unsigned int request; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void set_anqp_req(unsigned int bit, const char *name, int local,
			 struct anqp_query_info *qi)
{
	qi->request |= bit;
	if (local) {
		wpa_printf(MSG_DEBUG, "ANQP: %s (local)", name);
	} else {
		wpa_printf(MSG_DEBUG, "ANQP: %s not available", name);
	}
}