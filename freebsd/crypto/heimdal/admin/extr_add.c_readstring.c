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
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdin ; 
 size_t strcspn (char*,char*) ; 

__attribute__((used)) static char *
readstring(const char *prompt, char *buf, size_t len)
{
    printf("%s", prompt);
    if (fgets(buf, len, stdin) == NULL)
	return NULL;
    buf[strcspn(buf, "\r\n")] = '\0';
    return buf;
}