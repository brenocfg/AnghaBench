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
struct foreach_data {char** princs; int count; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 char** realloc (char**,int) ; 

__attribute__((used)) static krb5_error_code
add_princ(struct foreach_data *d, char *princ)
{
    char **tmp;
    tmp = realloc(d->princs, (d->count + 1) * sizeof(*tmp));
    if(tmp == NULL)
	return ENOMEM;
    d->princs = tmp;
    d->princs[d->count++] = princ;
    return 0;
}