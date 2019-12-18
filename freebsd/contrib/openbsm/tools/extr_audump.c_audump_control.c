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
 int PATH_MAX ; 
 scalar_t__ au_poltostr (long,int,char*) ; 
 scalar_t__ au_strtopol (char*,long*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int getacdir (char*,int) ; 
 int getacexpire (int*,int /*<<< orphan*/ *,size_t*) ; 
 int getacfilesz (size_t*) ; 
 int getacflg (char*,int) ; 
 int getachost (char*,int) ; 
 int getacmin (int*) ; 
 int getacna (char*,int) ; 
 int getacpol (char*,int) ; 
 int getacqsize (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setac () ; 

__attribute__((used)) static void
audump_control(void)
{
	char string[PATH_MAX], string2[PATH_MAX];
	int ret, val, qsz;
	long policy;
	time_t age;
	size_t size;

	ret = getacflg(string, PATH_MAX);
	if (ret == -2)
		err(-1, "getacflg");
	if (ret != 0)
		errx(-1, "getacflg: %d", ret);

	printf("flags:%s\n", string);

	ret = getacmin(&val);
	if (ret == -2)
		err(-1, "getacmin");
	if (ret != 0)
		errx(-1, "getacmin: %d", ret);

	printf("min:%d\n", val);

	ret = getacna(string, PATH_MAX);
	if (ret == -2)
		err(-1, "getacna");
	if (ret != 0)
		errx(-1, "getacna: %d", ret);

	printf("naflags:%s\n", string);

	setac();
	do {
		ret = getacdir(string, PATH_MAX);
		if (ret == -1)
			break;
		if (ret == -2)
			err(-1, "getacdir");
		if (ret != 0)
			errx(-1, "getacdir: %d", ret);
		printf("dir:%s\n", string);

	} while (ret == 0);

	ret = getacpol(string, PATH_MAX);
	if (ret != 0)
		err(-1, "getacpol");
	if (au_strtopol(string, &policy) < 0)
		err(-1, "au_strtopol");
	if (au_poltostr(policy, PATH_MAX, string2) < 0)
		err(-1, "au_poltostr");
	printf("policy:%s\n", string2);

	ret = getacfilesz(&size);
	if (ret == -2)
		err(-1, "getacfilesz");
	if (ret != 0)
		err(-1, "getacfilesz: %d", ret);

	printf("filesz:%ldB\n", size);

	ret = getacqsize(&qsz);
	if (ret == -2)
		err(-1, "getacqsize");
	if (ret != 0)
		err(-1, "getacqzize: %d", ret);

	printf("qsize:%d\n", qsz);

	ret = getachost(string, PATH_MAX);
	if (ret == -2)
		err(-1, "getachost");
	if (ret == -3)
		err(-1, "getachost: %d", ret);
	if (ret == 0 && ret != 1)
		printf("host:%s\n", string);

	ret = getacexpire(&val, &age, &size);
	if (ret == -2)
		err(-1, "getacexpire");
	if (ret == -1)
		err(-1, "getacexpire: %d", ret);
	if (ret == 0 && ret != 1)
		printf("expire-after:%ldB  %s %lds\n", size,
		    val ? "AND" : "OR", age);
}