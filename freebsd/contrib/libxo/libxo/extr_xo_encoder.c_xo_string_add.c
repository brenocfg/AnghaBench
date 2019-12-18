#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* xs_data; } ;
typedef  TYPE_1__ xo_string_node_t ;
typedef  int /*<<< orphan*/  xo_string_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 TYPE_1__* xo_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xo_string_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xs_link ; 

__attribute__((used)) static inline xo_string_node_t *
xo_string_add (xo_string_list_t *listp, const char *str)
{
    if (listp == NULL || str == NULL)
	return NULL;

    xo_string_list_init(listp);
    size_t len = strlen(str);
    xo_string_node_t *xsp;

    xsp = xo_realloc(NULL, sizeof(*xsp) + len + 1);
    if (xsp) {
	memcpy(xsp->xs_data, str, len);
	xsp->xs_data[len] = '\0';
	TAILQ_INSERT_TAIL(listp, xsp, xs_link);
    }

    return xsp;
}