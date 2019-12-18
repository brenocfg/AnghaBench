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
struct TYPE_3__ {void* path; void* authority; int /*<<< orphan*/  _port; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ h2o_url_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 void* h2o_iovec_init (char const*,...) ; 
 char* h2o_url_parse_hostport (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_authority_and_path(const char *src, const char *url_end, h2o_url_t *parsed)
{
    const char *p = h2o_url_parse_hostport(src, url_end - src, &parsed->host, &parsed->_port);
    if (p == NULL)
        return -1;
    parsed->authority = h2o_iovec_init(src, p - src);
    if (p == url_end) {
        parsed->path = h2o_iovec_init(H2O_STRLIT("/"));
    } else {
        if (*p != '/')
            return -1;
        parsed->path = h2o_iovec_init(p, url_end - p);
    }
    return 0;
}