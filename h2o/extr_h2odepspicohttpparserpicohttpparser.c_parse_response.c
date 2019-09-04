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
 int /*<<< orphan*/  PARSE_INT_3 (int*) ; 
 char* get_token_to_eol (char const*,char const*,char const**,size_t*,int*) ; 
 char const* parse_headers (char const*,char const*,struct phr_header*,size_t*,size_t,int*) ; 
 char* parse_http_version (char const*,char const*,int*,int*) ; 

__attribute__((used)) static const char *parse_response(const char *buf, const char *buf_end, int *minor_version, int *status, const char **msg,
                                  size_t *msg_len, struct phr_header *headers, size_t *num_headers, size_t max_headers, int *ret)
{
    /* parse "HTTP/1.x" */
    if ((buf = parse_http_version(buf, buf_end, minor_version, ret)) == NULL) {
        return NULL;
    }
    /* skip space */
    if (*buf++ != ' ') {
        *ret = -1;
        return NULL;
    }
    /* parse status code, we want at least [:digit:][:digit:][:digit:]<other char> to try to parse */
    if (buf_end - buf < 4) {
        *ret = -2;
        return NULL;
    }
    PARSE_INT_3(status);

    /* skip space */
    if (*buf++ != ' ') {
        *ret = -1;
        return NULL;
    }
    /* get message */
    if ((buf = get_token_to_eol(buf, buf_end, msg, msg_len, ret)) == NULL) {
        return NULL;
    }

    return parse_headers(buf, buf_end, headers, num_headers, max_headers, ret);
}