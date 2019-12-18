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
typedef  struct sockaddr const sockaddr ;
struct evhttp_connection {scalar_t__ conn_address; } ;

/* Variables and functions */

const struct sockaddr*
evhttp_connection_get_addr(struct evhttp_connection *evcon)
{
	return (struct sockaddr *)evcon->conn_address;
}