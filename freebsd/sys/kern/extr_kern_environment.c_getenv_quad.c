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
typedef  int /*<<< orphan*/  value ;
typedef  int quad_t ;

/* Variables and functions */
 int /*<<< orphan*/  KENV_MNAMELEN ; 
 scalar_t__ KENV_MVALLEN ; 
 int /*<<< orphan*/  getenv_string (char const*,char*,int) ; 
 int strtoq (char*,char**,int /*<<< orphan*/ ) ; 

int
getenv_quad(const char *name, quad_t *data)
{
	char	value[KENV_MNAMELEN + 1 + KENV_MVALLEN + 1];
	char	*vtp;
	quad_t	iv;

	if (!getenv_string(name, value, sizeof(value)))
		return (0);
	iv = strtoq(value, &vtp, 0);
	if (vtp == value || (vtp[0] != '\0' && vtp[1] != '\0'))
		return (0);
	switch (vtp[0]) {
	case 't': case 'T':
		iv *= 1024;
		/* FALLTHROUGH */
	case 'g': case 'G':
		iv *= 1024;
		/* FALLTHROUGH */
	case 'm': case 'M':
		iv *= 1024;
		/* FALLTHROUGH */
	case 'k': case 'K':
		iv *= 1024;
	case '\0':
		break;
	default:
		return (0);
	}
	*data = iv;
	return (1);
}