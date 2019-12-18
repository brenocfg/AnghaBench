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
struct evhttp_request {int type; } ;
typedef  enum evhttp_cmd_type { ____Placeholder_evhttp_cmd_type } evhttp_cmd_type ;

/* Variables and functions */

enum evhttp_cmd_type
evhttp_request_get_command(const struct evhttp_request *req) {
	return (req->type);
}