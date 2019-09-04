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
struct phr_header {char const* name; int name_len; int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  ranges1 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_EOF () ; 
 int /*<<< orphan*/  EXPECT_CHAR (char) ; 
 char* findchar_fast (char const*,char const*,char const*,int,int*) ; 
 char* get_token_to_eol (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * token_char_map ; 

__attribute__((used)) static const char *parse_headers(const char *buf, const char *buf_end, struct phr_header *headers, size_t *num_headers,
                                 size_t max_headers, int *ret)
{
    for (;; ++*num_headers) {
        CHECK_EOF();
        if (*buf == '\015') {
            ++buf;
            EXPECT_CHAR('\012');
            break;
        } else if (*buf == '\012') {
            ++buf;
            break;
        }
        if (*num_headers == max_headers) {
            *ret = -1;
            return NULL;
        }
        if (!(*num_headers != 0 && (*buf == ' ' || *buf == '\t'))) {
            /* parsing name, but do not discard SP before colon, see
             * http://www.mozilla.org/security/announce/2006/mfsa2006-33.html */
            headers[*num_headers].name = buf;
            static const char ranges1[] __attribute__((aligned(16))) = "\x00 "  /* control chars and up to SP */
                                                                       "\"\""   /* 0x22 */
                                                                       "()"     /* 0x28,0x29 */
                                                                       ",,"     /* 0x2c */
                                                                       "//"     /* 0x2f */
                                                                       ":@"     /* 0x3a-0x40 */
                                                                       "[]"     /* 0x5b-0x5d */
                                                                       "{\377"; /* 0x7b-0xff */
            int found;
            buf = findchar_fast(buf, buf_end, ranges1, sizeof(ranges1) - 1, &found);
            if (!found) {
                CHECK_EOF();
            }
            while (1) {
                if (*buf == ':') {
                    break;
                } else if (!token_char_map[(unsigned char)*buf]) {
                    *ret = -1;
                    return NULL;
                }
                ++buf;
                CHECK_EOF();
            }
            if ((headers[*num_headers].name_len = buf - headers[*num_headers].name) == 0) {
                *ret = -1;
                return NULL;
            }
            ++buf;
            for (;; ++buf) {
                CHECK_EOF();
                if (!(*buf == ' ' || *buf == '\t')) {
                    break;
                }
            }
        } else {
            headers[*num_headers].name = NULL;
            headers[*num_headers].name_len = 0;
        }
        if ((buf = get_token_to_eol(buf, buf_end, &headers[*num_headers].value, &headers[*num_headers].value_len, ret)) == NULL) {
            return NULL;
        }
    }
    return buf;
}