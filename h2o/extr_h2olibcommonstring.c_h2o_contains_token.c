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
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_iovec_init (char const*,size_t) ; 
 scalar_t__ h2o_lcstris (char const*,size_t,char const*,size_t) ; 
 char* h2o_next_token (int /*<<< orphan*/ *,int,size_t*,int /*<<< orphan*/ *) ; 

int h2o_contains_token(const char *haysack, size_t haysack_len, const char *needle, size_t needle_len, int separator)
{
    h2o_iovec_t iter = h2o_iovec_init(haysack, haysack_len);
    const char *token = NULL;
    size_t token_len = 0;

    while ((token = h2o_next_token(&iter, separator, &token_len, NULL)) != NULL) {
        if (h2o_lcstris(token, token_len, needle, needle_len)) {
            return 1;
        }
    }
    return 0;
}