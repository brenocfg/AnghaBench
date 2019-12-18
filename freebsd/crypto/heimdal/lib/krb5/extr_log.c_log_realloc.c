#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct facility {int dummy; } ;
struct TYPE_3__ {int len; struct facility* val; } ;
typedef  TYPE_1__ krb5_log_facility ;

/* Variables and functions */
 struct facility* realloc (struct facility*,int) ; 

__attribute__((used)) static struct facility*
log_realloc(krb5_log_facility *f)
{
    struct facility *fp;
    fp = realloc(f->val, (f->len + 1) * sizeof(*f->val));
    if(fp == NULL)
	return NULL;
    f->len++;
    f->val = fp;
    fp += f->len - 1;
    return fp;
}