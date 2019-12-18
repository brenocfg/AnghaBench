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
struct TYPE_3__ {char* name; int /*<<< orphan*/  (* Data ) (char const*,size_t,char*) ;} ;
typedef  TYPE_1__ Algorithm_t ;

/* Variables and functions */
 int HEX_DIGEST_LENGTH ; 
 scalar_t__ checkAgainst ; 
 int /*<<< orphan*/  checksFailed ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ qflag ; 
 scalar_t__ rflag ; 
 scalar_t__ strcasecmp (char*,scalar_t__) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (char const*,size_t,char*) ; 

__attribute__((used)) static void
MDString(const Algorithm_t *alg, const char *string)
{
	size_t len = strlen(string);
	char buf[HEX_DIGEST_LENGTH];

	alg->Data(string,len,buf);
	if (qflag)
		printf("%s", buf);
	else if (rflag)
		printf("%s \"%s\"", buf, string);
	else
		printf("%s (\"%s\") = %s", alg->name, string, buf);
	if (checkAgainst && strcasecmp(buf,checkAgainst) != 0)
	{
		checksFailed++;
		if (!qflag)
			printf(" [ failed ]");
	}
	printf("\n");
}