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
typedef  int /*<<< orphan*/  va_list ;
struct nv {scalar_t__ nv_error; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  NV_TYPE_STRING ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nv_add (struct nv*,unsigned char const*,int,int /*<<< orphan*/ ,char const*) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 

void
nv_add_stringv(struct nv *nv, const char *name, const char *valuefmt,
    va_list valueap)
{
	char *value;
	ssize_t size;

	size = vasprintf(&value, valuefmt, valueap);
	if (size == -1) {
		if (nv->nv_error == 0)
			nv->nv_error = ENOMEM;
		return;
	}
	size++;
	nv_add(nv, (const unsigned char *)value, size, NV_TYPE_STRING, name);
	free(value);
}