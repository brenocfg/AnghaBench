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
struct TYPE_3__ {char* data; int size; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
killproto(DBT *key)
{
	char *p, *d = key->data;

	if ((p = strchr(d, '/')) == NULL)
		abort();
	*p++ = '\0';
	key->size = p - d;
}