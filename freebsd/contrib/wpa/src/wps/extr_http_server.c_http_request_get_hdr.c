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
struct http_request {int /*<<< orphan*/  hread; } ;

/* Variables and functions */
 char* httpread_hdr_get (int /*<<< orphan*/ ) ; 

char * http_request_get_hdr(struct http_request *req)
{
	return httpread_hdr_get(req->hread);
}