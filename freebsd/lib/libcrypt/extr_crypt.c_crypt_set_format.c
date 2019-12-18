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
struct crypt_format {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct crypt_format const* crypt_format ; 
 struct crypt_format* crypt_formats ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char const*) ; 

int
crypt_set_format(const char *format)
{
	const struct crypt_format *cf;

	for (cf = crypt_formats; cf->name != NULL; ++cf) {
		if (strcasecmp(cf->name, format) == 0) {
			crypt_format = cf;
			return (1);
		}
	}
	return (0);
}