#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {size_t size; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {scalar_t__ tmp_key; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ DBT ;
typedef  int /*<<< orphan*/  BUFHEAD ;

/* Variables and functions */
 scalar_t__ collect_key (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

int
__big_keydata(HTAB *hashp, BUFHEAD *bufp, DBT *key, DBT *val, int set)
{
	key->size = (size_t)collect_key(hashp, bufp, 0, val, set);
	if (key->size == (size_t)-1)
		return (-1);
	key->data = (u_char *)hashp->tmp_key;
	return (0);
}