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
struct Strbuf {int /*<<< orphan*/  s; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_item ; 
 int /*<<< orphan*/ * tw_str_add (int /*<<< orphan*/ *,scalar_t__) ; 

void
tw_item_add(const struct Strbuf *s)
{
    Char *p;

    p = tw_str_add(&tw_item, s->len + 1);
    Strcpy(p, s->s);
}