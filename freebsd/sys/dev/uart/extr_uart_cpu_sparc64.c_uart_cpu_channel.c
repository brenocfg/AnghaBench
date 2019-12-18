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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  alias ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getprop (int,char*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
uart_cpu_channel(char *dev)
{
	char alias[64];
	phandle_t aliases;
	int len;
	const char *p;

	strcpy(alias, dev);
	if ((aliases = OF_finddevice("/aliases")) != -1)
		(void)OF_getprop(aliases, dev, alias, sizeof(alias));
	len = strlen(alias);
	if ((p = strrchr(alias, ':')) == NULL)
		return (0);
	p++;
	if (p - alias == len - 1 && (*p == 'a' || *p == 'b'))
		return (*p - 'a' + 1);
	if (strcmp(p, "ssp") == 0)
		return (1);
	return (0);
}