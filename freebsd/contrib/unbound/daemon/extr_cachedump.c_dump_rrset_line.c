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
typedef  int /*<<< orphan*/  time_t ;
struct ub_packed_rrset_key {int dummy; } ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  packed_rr_to_string (struct ub_packed_rrset_key*,size_t,int /*<<< orphan*/ ,char*,int) ; 
 int ssl_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
dump_rrset_line(RES* ssl, struct ub_packed_rrset_key* k, time_t now, size_t i)
{
	char s[65535];
	if(!packed_rr_to_string(k, i, now, s, sizeof(s))) {
		return ssl_printf(ssl, "BADRR\n");
	}
	return ssl_printf(ssl, "%s", s);
}