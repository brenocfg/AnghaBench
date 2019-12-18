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
struct phr_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_TOKEN (char const*,size_t) ; 
 int /*<<< orphan*/  CHECK_EOF () ; 
 int /*<<< orphan*/  EXPECT_CHAR (char) ; 
 char const* parse_headers (char const*,char const*,struct phr_header*,size_t*,size_t,int*) ; 
 char* parse_http_version (char const*,char const*,int*,int*) ; 

__attribute__((used)) static const char *parse_request(const char *buf, const char *buf_end, const char **method, size_t *method_len, const char **path,
                                 size_t *path_len, int *minor_version, struct phr_header *headers, size_t *num_headers,
                                 size_t max_headers, int *ret)
{
    /* skip first empty line (some clients add CRLF after POST content) */
    CHECK_EOF();
    if (*buf == '\015') {
        ++buf;
        EXPECT_CHAR('\012');
    } else if (*buf == '\012') {
        ++buf;
    }

    /* parse request line */
    ADVANCE_TOKEN(*method, *method_len);
    ++buf;
    ADVANCE_TOKEN(*path, *path_len);
    ++buf;
    if (*method_len == 0 || *path_len == 0) {
        *ret = -1;
        return NULL;
    }
    if ((buf = parse_http_version(buf, buf_end, minor_version, ret)) == NULL) {
        return NULL;
    }
    if (*buf == '\015') {
        ++buf;
        EXPECT_CHAR('\012');
    } else if (*buf == '\012') {
        ++buf;
    } else {
        *ret = -1;
        return NULL;
    }

    return parse_headers(buf, buf_end, headers, num_headers, max_headers, ret);
}