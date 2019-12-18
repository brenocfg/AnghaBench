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
struct keys {int dummy; } ;

/* Variables and functions */
 int asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  keys_add (struct keys*,char const*,char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

void
keys_add_int(struct keys *keys, const char *name, int value)
{
	char *str;
	int ret;

	ret = asprintf(&str, "%d", value);
	if (ret <= 0)
		log_err(1, "asprintf");

	keys_add(keys, name, str);
	free(str);
}