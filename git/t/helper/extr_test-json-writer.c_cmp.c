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
struct TYPE_2__ {char* buf; } ;
struct json_writer {TYPE_1__ json; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static void cmp(const char *test, const struct json_writer *jw, const char *exp)
{
	if (!strcmp(jw->json.buf, exp))
		return;

	printf("error[%s]: observed '%s' expected '%s'\n",
	       test, jw->json.buf, exp);
	exit(1);
}