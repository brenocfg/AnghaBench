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
typedef  enum httpread_hdr_type { ____Placeholder_httpread_hdr_type } httpread_hdr_type ;

/* Variables and functions */
 int httpread_hdr_type_get (int /*<<< orphan*/ ) ; 

enum httpread_hdr_type http_request_get_type(struct http_request *req)
{
	return httpread_hdr_type_get(req->hread);
}