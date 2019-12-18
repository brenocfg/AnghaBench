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
 scalar_t__ isalnum (unsigned char) ; 
 int /*<<< orphan*/  printf (char*,unsigned char) ; 
 int /*<<< orphan*/  putchar (char const) ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 

__attribute__((used)) static void
http_encode(const char *p)
{
	for (; *p != '\0'; p++) {
		if (isalnum((unsigned char)*p) == 0 &&
		    strchr("-._~", *p) == NULL)
			printf("%%%2.2X", (unsigned char)*p);
		else
			putchar(*p);
	}
}