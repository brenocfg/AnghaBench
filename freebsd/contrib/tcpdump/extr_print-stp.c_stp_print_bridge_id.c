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
typedef  int u_char ;
typedef  int /*<<< orphan*/  bridge_id_str ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int const,int const,int const,int const,int const,int const,int const,int const) ; 

__attribute__((used)) static char *
stp_print_bridge_id(const u_char *p)
{
    static char bridge_id_str[sizeof("pppp.aa:bb:cc:dd:ee:ff")];

    snprintf(bridge_id_str, sizeof(bridge_id_str),
             "%.2x%.2x.%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
             p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);

    return bridge_id_str;
}