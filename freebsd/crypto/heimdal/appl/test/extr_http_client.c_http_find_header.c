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
struct http_req {int num_headers; char const** headers; } ;

/* Variables and functions */
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

__attribute__((used)) static const char *
http_find_header(struct http_req *req, const char *header)
{
    int i, len = strlen(header);

    for (i = 0; i < req->num_headers; i++) {
	if (strncasecmp(header, req->headers[i], len) == 0) {
	    return req->headers[i] + len + 1;
	}
    }
    return NULL;
}