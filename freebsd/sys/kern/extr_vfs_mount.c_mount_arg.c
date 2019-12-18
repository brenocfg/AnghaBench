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
struct mntarg {int len; TYPE_1__* v; scalar_t__ error; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MOUNT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 struct mntarg* malloc (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* realloc (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 
 void* strlen (void const*) ; 

struct mntarg *
mount_arg(struct mntarg *ma, const char *name, const void *val, int len)
{

	if (ma == NULL) {
		ma = malloc(sizeof *ma, M_MOUNT, M_WAITOK | M_ZERO);
		SLIST_INIT(&ma->list);
	}
	if (ma->error)
		return (ma);

	ma->v = realloc(ma->v, sizeof *ma->v * (ma->len + 2),
	    M_MOUNT, M_WAITOK);
	ma->v[ma->len].iov_base = (void *)(uintptr_t)name;
	ma->v[ma->len].iov_len = strlen(name) + 1;
	ma->len++;

	ma->v[ma->len].iov_base = (void *)(uintptr_t)val;
	if (len < 0)
		ma->v[ma->len].iov_len = strlen(val) + 1;
	else
		ma->v[ma->len].iov_len = len;
	ma->len++;
	return (ma);
}