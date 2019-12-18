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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  keyid_t ;

/* Variables and functions */
 int /*<<< orphan*/  MD5auth_setkey (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

int
authusekey(
	keyid_t keyno,
	int keytype,
	const u_char *str
	)
{
	size_t	len;

	len = strlen((const char *)str);
	if (0 == len)
		return 0;

	MD5auth_setkey(keyno, keytype, str, len, NULL);
	return 1;
}