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

/* Variables and functions */
 int h2o_memis (char const*,size_t,char const*,size_t) ; 

int h2o_filecache_compare_etag_strong(const char *tag1, size_t tag1_len, const char *tag2, size_t tag2_len)
{
    size_t i;

    /* first check if tag1 a valid strong etag, then just strictly compare tag1 with tag2 */
    if (tag1_len < sizeof("\"\"")) /* strong etag should be at least one character quoted */
        return 0;
    if (tag1[0] != '"' || tag1[tag1_len - 1] != '"') /* not a valid etag */
        return 0;
    for (i = 1; i < tag1_len - 1; i++) {
        if (tag1[i] < 0x21 || tag1[i] == '"') /* VCHAR except double quotes, plus obs-text */
            return 0;
    }
    return h2o_memis(tag1, tag1_len, tag2, tag2_len);
}