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
typedef  int /*<<< orphan*/  krb5_error_code ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  HDB_ERR_CANT_LOCK_DB ; 
 int /*<<< orphan*/  HDB_ERR_DB_INUSE ; 
 int HDB_RLOCK ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 int LOCK_SH ; 
 scalar_t__ errno ; 
 int flock (int,int) ; 
 int /*<<< orphan*/  sleep (int) ; 

krb5_error_code
hdb_lock(int fd, int operation)
{
    int i, code = 0;

    for(i = 0; i < 3; i++){
	code = flock(fd, (operation == HDB_RLOCK ? LOCK_SH : LOCK_EX) | LOCK_NB);
	if(code == 0 || errno != EWOULDBLOCK)
	    break;
	sleep(1);
    }
    if(code == 0)
	return 0;
    if(errno == EWOULDBLOCK)
	return HDB_ERR_DB_INUSE;
    return HDB_ERR_CANT_LOCK_DB;
}