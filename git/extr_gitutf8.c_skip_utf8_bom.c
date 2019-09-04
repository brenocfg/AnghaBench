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
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_bom ; 

int skip_utf8_bom(char **text, size_t len)
{
	if (len < strlen(utf8_bom) ||
	    memcmp(*text, utf8_bom, strlen(utf8_bom)))
		return 0;
	*text += strlen(utf8_bom);
	return 1;
}