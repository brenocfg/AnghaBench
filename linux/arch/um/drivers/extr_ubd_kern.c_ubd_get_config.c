#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* file; } ;
struct ubd {char* file; TYPE_1__ cow; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CHUNK (char*,int,int,char*,int) ; 
 int MAX_DEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int parse_unit (char**) ; 
 struct ubd* ubd_devs ; 
 int /*<<< orphan*/  ubd_lock ; 

__attribute__((used)) static int ubd_get_config(char *name, char *str, int size, char **error_out)
{
	struct ubd *ubd_dev;
	int n, len = 0;

	n = parse_unit(&name);
	if((n >= MAX_DEV) || (n < 0)){
		*error_out = "ubd_get_config : device number out of range";
		return -1;
	}

	ubd_dev = &ubd_devs[n];
	mutex_lock(&ubd_lock);

	if(ubd_dev->file == NULL){
		CONFIG_CHUNK(str, size, len, "", 1);
		goto out;
	}

	CONFIG_CHUNK(str, size, len, ubd_dev->file, 0);

	if(ubd_dev->cow.file != NULL){
		CONFIG_CHUNK(str, size, len, ",", 0);
		CONFIG_CHUNK(str, size, len, ubd_dev->cow.file, 1);
	}
	else CONFIG_CHUNK(str, size, len, "", 1);

 out:
	mutex_unlock(&ubd_lock);
	return len;
}