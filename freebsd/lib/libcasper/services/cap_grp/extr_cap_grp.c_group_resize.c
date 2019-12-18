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
 int ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 char* gbuffer ; 
 int gbufsize ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* realloc (char*,int) ; 

__attribute__((used)) static int
group_resize(void)
{
	char *buf;

	if (gbufsize == 0)
		gbufsize = 1024;
	else
		gbufsize *= 2;

	buf = gbuffer;
	gbuffer = realloc(buf, gbufsize);
	if (gbuffer == NULL) {
		free(buf);
		gbufsize = 0;
		return (ENOMEM);
	}
	memset(gbuffer, 0, gbufsize);

	return (0);
}