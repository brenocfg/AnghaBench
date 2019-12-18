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
#define  ECONNREFUSED 131 
#define  EMSGSIZE 130 
#define  ENOENT 129 
#define  ENOMEM 128 
 int /*<<< orphan*/  HES_ER_CONFIG ; 
 int /*<<< orphan*/  HES_ER_NET ; 
 int /*<<< orphan*/  HES_ER_NOTFOUND ; 
 int errno ; 
 int /*<<< orphan*/  errval ; 

__attribute__((used)) static void
translate_errors()
{
	switch (errno) {
	case ENOENT:
		errval = HES_ER_NOTFOUND;
		break;
	case ECONNREFUSED:
	case EMSGSIZE:
		errval = HES_ER_NET;
		break;
	case ENOMEM:
	default:
		/* Not a good match, but the best we can do. */
		errval = HES_ER_CONFIG;
		break;
	}
}