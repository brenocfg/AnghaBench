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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strsave (int /*<<< orphan*/ ) ; 
 scalar_t__ blklen (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** xcalloc (scalar_t__,int) ; 

Char  **
saveblk(Char **v)
{
    Char **newv, **onewv;

    if (v == NULL)
	return NULL;

    onewv = newv = xcalloc(blklen(v) + 1, sizeof(Char **));

    while (*v)
	*newv++ = Strsave(*v++);
    return (onewv);
}