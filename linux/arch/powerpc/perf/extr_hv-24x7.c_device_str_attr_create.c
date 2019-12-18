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
struct attribute {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct attribute* device_str_attr_create_ (char*,char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int,char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* memdup_to_str (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct attribute *device_str_attr_create(char *name, int name_max,
						int name_nonce,
						char *str, size_t str_max)
{
	char *n;
	char *s = memdup_to_str(str, str_max, GFP_KERNEL);
	struct attribute *a;

	if (!s)
		return NULL;

	if (!name_nonce)
		n = kasprintf(GFP_KERNEL, "%.*s", name_max, name);
	else
		n = kasprintf(GFP_KERNEL, "%.*s__%d", name_max, name,
					name_nonce);
	if (!n)
		goto out_s;

	a = device_str_attr_create_(n, s);
	if (!a)
		goto out_n;

	return a;
out_n:
	kfree(n);
out_s:
	kfree(s);
	return NULL;
}