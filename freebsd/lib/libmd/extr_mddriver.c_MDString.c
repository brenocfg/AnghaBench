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

/* Variables and functions */
 int MD ; 
 char* MDData (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void 
MDString(char *string)
{
	char buf[33];

	printf("MD%d (\"%s\") = %s\n",
	       MD, string, MDData(string, strlen(string), buf));
}