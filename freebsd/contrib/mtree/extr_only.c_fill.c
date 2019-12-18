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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash_find (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_insert (char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
fill(char *str)
{
	uint32_t h;
	char *ptr = strrchr(str, '/');

	if (ptr == NULL)
		return;

	*ptr = '\0';
	if (!hash_find(str, &h)) {
		hash_insert(str, h);
		fill(str);
	}
	*ptr = '/';
}