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
typedef  int /*<<< orphan*/  yajl_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,unsigned char*) ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yajl_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yajl_allow_comments ; 
 int /*<<< orphan*/  yajl_allow_multiple_values ; 
 int /*<<< orphan*/  yajl_complete_parse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  yajl_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_free_error (int /*<<< orphan*/ ,unsigned char*) ; 
 unsigned char* yajl_get_error (int /*<<< orphan*/ ,int,unsigned char const*,size_t const) ; 
 scalar_t__ yajl_parse (int /*<<< orphan*/ ,unsigned char const*,size_t const) ; 
 scalar_t__ yajl_status_ok ; 

bool json_validate(const char *buf, const size_t len) {
    bool valid = true;
    yajl_handle hand = yajl_alloc(NULL, NULL, NULL);
    /* Allowing comments allows for more user-friendly layout files. */
    yajl_config(hand, yajl_allow_comments, true);
    /* Allow multiple values, i.e. multiple nodes to attach */
    yajl_config(hand, yajl_allow_multiple_values, true);

    setlocale(LC_NUMERIC, "C");
    if (yajl_parse(hand, (const unsigned char *)buf, len) != yajl_status_ok) {
        unsigned char *str = yajl_get_error(hand, 1, (const unsigned char *)buf, len);
        ELOG("JSON parsing error: %s\n", str);
        yajl_free_error(hand, str);
        valid = false;
    }
    setlocale(LC_NUMERIC, "");

    yajl_complete_parse(hand);
    yajl_free(hand);

    return valid;
}