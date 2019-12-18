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
struct st_session_ticket_t {scalar_t__ not_before; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ticket_sort_compare(const void *_x, const void *_y)
{
    struct st_session_ticket_t *x = *(void **)_x, *y = *(void **)_y;

    if (x->not_before != y->not_before)
        return x->not_before > y->not_before ? -1 : 1;
    return memcmp(x->name, y->name, sizeof(x->name));
}