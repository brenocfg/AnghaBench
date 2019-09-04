#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ h2o_token_t ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* h2o_lookup_token (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* h2o_mem_alloc (int) ; 
 TYPE_2__ h2o_str_stripws (char const*,size_t) ; 
 TYPE_2__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  h2o_strtolower (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int extract_name(const char *src, size_t len, h2o_iovec_t **_name)
{
    h2o_iovec_t name;
    const h2o_token_t *name_token;

    name = h2o_str_stripws(src, len);
    if (name.len == 0)
        return -1;

    name = h2o_strdup(NULL, name.base, name.len);
    h2o_strtolower(name.base, name.len);

    if ((name_token = h2o_lookup_token(name.base, name.len)) != NULL) {
        *_name = (h2o_iovec_t *)&name_token->buf;
        free(name.base);
    } else {
        *_name = h2o_mem_alloc(sizeof(**_name));
        **_name = name;
    }

    return 0;
}