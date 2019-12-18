#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct TYPE_6__ {scalar_t__ internal; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ HTAB ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_2__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ERROR ; 
 int /*<<< orphan*/  HASH_GET ; 
 int /*<<< orphan*/  errno ; 
 int hash_access (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hash_get(const DB *dbp, const DBT *key, DBT *data, u_int32_t flag)
{
	HTAB *hashp;

	hashp = (HTAB *)dbp->internal;
	if (flag) {
		hashp->error = errno = EINVAL;
		return (ERROR);
	}
	return (hash_access(hashp, HASH_GET, (DBT *)key, data));
}