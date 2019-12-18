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
typedef  void* u8 ;
struct tlsv1_server {void* alert_description; void* alert_level; } ;

/* Variables and functions */

void tlsv1_server_alert(struct tlsv1_server *conn, u8 level, u8 description)
{
	conn->alert_level = level;
	conn->alert_description = description;
}