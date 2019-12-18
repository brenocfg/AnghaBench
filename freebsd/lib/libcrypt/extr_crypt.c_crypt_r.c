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
struct crypt_format {int (* func ) (char const*,char const*,char*) ;int /*<<< orphan*/ * magic; int /*<<< orphan*/ * name; } ;
struct crypt_data {char* __buf; } ;
struct TYPE_2__ {int (* func ) (char const*,char const*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DES_SALT_ALPHABET ; 
 int crypt_des (char const*,char const*,char*) ; 
 TYPE_1__* crypt_format ; 
 struct crypt_format* crypt_formats ; 
 int strlen (char const*) ; 
 int strspn (char const*,int /*<<< orphan*/ ) ; 
 char const* strstr (char const*,int /*<<< orphan*/ *) ; 

char *
crypt_r(const char *passwd, const char *salt, struct crypt_data *data)
{
	const struct crypt_format *cf;
	int (*func)(const char *, const char *, char *);
#ifdef HAS_DES
	int len;
#endif

	for (cf = crypt_formats; cf->name != NULL; ++cf)
		if (cf->magic != NULL && strstr(salt, cf->magic) == salt) {
			func = cf->func;
			goto match;
		}
#ifdef HAS_DES
	len = strlen(salt);
	if ((len == 13 || len == 2) && strspn(salt, DES_SALT_ALPHABET) == len) {
		func = crypt_des;
		goto match;
	}
#endif
	func = crypt_format->func;
match:
	if (func(passwd, salt, data->__buf) != 0)
		return (NULL);
	return (data->__buf);
}