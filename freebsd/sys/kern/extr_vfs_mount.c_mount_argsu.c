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
struct mntarg {int /*<<< orphan*/  error; int /*<<< orphan*/  list; } ;
struct mntaarg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MOUNT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct mntaarg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyinstr (void const*,char*,int,int /*<<< orphan*/ *) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 struct mntarg* mount_arg (struct mntarg*,char const*,char*,int) ; 
 int /*<<< orphan*/  next ; 

struct mntarg *
mount_argsu(struct mntarg *ma, const char *name, const void *val, int len)
{
	struct mntaarg *maa;
	char *tbuf;

	if (val == NULL)
		return (ma);
	if (ma == NULL) {
		ma = malloc(sizeof *ma, M_MOUNT, M_WAITOK | M_ZERO);
		SLIST_INIT(&ma->list);
	}
	if (ma->error)
		return (ma);
	maa = malloc(sizeof *maa + len, M_MOUNT, M_WAITOK | M_ZERO);
	SLIST_INSERT_HEAD(&ma->list, maa, next);
	tbuf = (void *)(maa + 1);
	ma->error = copyinstr(val, tbuf, len, NULL);
	return (mount_arg(ma, name, tbuf, -1));
}