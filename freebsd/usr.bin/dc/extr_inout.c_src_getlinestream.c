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
struct TYPE_2__ {int /*<<< orphan*/  stream; } ;
struct source {TYPE_1__ u; } ;

/* Variables and functions */
 int BUFSIZ ; 
 char* bstrdup (char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
src_getlinestream(struct source *src)
{
	char buf[BUFSIZ];

	if (fgets(buf, BUFSIZ, src->u.stream) == NULL)
		return (bstrdup(""));
	return bstrdup(buf);
}