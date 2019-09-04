#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ use_ssl; } ;
typedef  TYPE_1__ gitno_connection_data ;

/* Variables and functions */
 char const* default_port_http ; 
 char const* default_port_https ; 

const char *gitno__default_port(
	gitno_connection_data *data)
{
	return data->use_ssl ? default_port_https : default_port_http;
}