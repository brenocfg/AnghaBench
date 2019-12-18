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
typedef  enum drbd_conns { ____Placeholder_drbd_conns } drbd_conns ;

/* Variables and functions */
 int C_BEHIND ; 
 char const** drbd_conn_s_names ; 

const char *drbd_conn_str(enum drbd_conns s)
{
	/* enums are unsigned... */
	return s > C_BEHIND ? "TOO_LARGE" : drbd_conn_s_names[s];
}