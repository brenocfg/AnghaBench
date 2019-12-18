#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ extract_name (char const*,int,TYPE_1__**) ; 
 TYPE_1__ h2o_str_stripws (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int extract_name_value(const char *src, h2o_iovec_t **name, h2o_iovec_t *value)
{
    const char *colon = strchr(src, ':');

    if (colon == NULL)
        return -1;

    if (extract_name(src, colon - src, name) != 0)
        return -1;
    *value = h2o_str_stripws(colon + 1, strlen(colon + 1));
    *value = h2o_strdup(NULL, value->base, value->len);

    return 0;
}