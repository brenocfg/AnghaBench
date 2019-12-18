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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ *) ; 
 char* ctime (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ctime_lock ; 
 int /*<<< orphan*/  ctime_r_cleanup ; 
 int ctime_r_init ; 
 int /*<<< orphan*/  lock_basic_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

char *ctime_r(const time_t *timep, char *buf)
{
	char* result;
	if(!ctime_r_init) {
		/* still small race where this init can be done twice,
		 * which is mostly harmless */
		ctime_r_init = 1;
		lock_basic_init(&ctime_lock);
		atexit(&ctime_r_cleanup);
	}
	lock_basic_lock(&ctime_lock);
	result = ctime(timep);
	if(buf && result) {
		if(strlen(result) > 10 && result[7]==' ' && result[8]=='0')
			result[8]=' '; /* fix error in windows ctime */
		strcpy(buf, result);
	}
	lock_basic_unlock(&ctime_lock);
	return result;
}