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

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int const,int const,int const,int const,int const,int const,int const,int const) ; 

__attribute__((used)) static const char *
format_id(const u_char *id)
{
    static char buf[25];
    snprintf(buf, 25, "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
             id[0], id[1], id[2], id[3], id[4], id[5], id[6], id[7]);
    buf[24] = '\0';
    return buf;
}