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
struct krb5_plugin {struct krb5_plugin* next; } ;

/* Variables and functions */

struct krb5_plugin *
_krb5_plugin_get_next(struct krb5_plugin *p)
{
    return p->next;
}