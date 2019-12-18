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
struct crypt_data {int dummy; } ;

/* Variables and functions */
 char* crypt_r (char const*,char const*,struct crypt_data*) ; 

char *
crypt(const char *passwd, const char *salt)
{
	static struct crypt_data data;

	return (crypt_r(passwd, salt, &data));
}