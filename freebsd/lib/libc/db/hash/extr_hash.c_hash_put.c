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
struct TYPE_5__ {int flags; void* error; } ;
typedef  TYPE_1__ HTAB ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_2__ DB ;

/* Variables and functions */
 void* EINVAL ; 
 void* EPERM ; 
 int ERROR ; 
 int /*<<< orphan*/  HASH_PUT ; 
 int /*<<< orphan*/  HASH_PUTNEW ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 scalar_t__ R_NOOVERWRITE ; 
 void* errno ; 
 int hash_access (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hash_put(const DB *dbp, DBT *key, const DBT *data, u_int32_t flag)
{
	HTAB *hashp;

	hashp = (HTAB *)dbp->internal;
	if (flag && flag != R_NOOVERWRITE) {
		hashp->error = errno = EINVAL;
		return (ERROR);
	}
	if ((hashp->flags & O_ACCMODE) == O_RDONLY) {
		hashp->error = errno = EPERM;
		return (ERROR);
	}
	return (hash_access(hashp, flag == R_NOOVERWRITE ?
	    HASH_PUTNEW : HASH_PUT, (DBT *)key, (DBT *)data));
}