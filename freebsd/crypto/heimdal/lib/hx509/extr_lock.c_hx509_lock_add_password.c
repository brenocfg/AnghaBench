#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_lock ;
struct TYPE_4__ {char** val; int len; } ;
struct TYPE_5__ {TYPE_1__ password; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 void* realloc (char**,int) ; 
 char* strdup (char const*) ; 

int
hx509_lock_add_password(hx509_lock lock, const char *password)
{
    void *d;
    char *s;

    s = strdup(password);
    if (s == NULL)
	return ENOMEM;

    d = realloc(lock->password.val,
		(lock->password.len + 1) * sizeof(lock->password.val[0]));
    if (d == NULL) {
	free(s);
	return ENOMEM;
    }
    lock->password.val = d;
    lock->password.val[lock->password.len] = s;
    lock->password.len++;

    return 0;
}