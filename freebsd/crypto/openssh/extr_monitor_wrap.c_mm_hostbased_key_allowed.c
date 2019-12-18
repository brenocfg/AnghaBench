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
struct sshkey {int dummy; } ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MM_HOSTKEY ; 
 int mm_key_allowed (int /*<<< orphan*/ ,char const*,char const*,struct sshkey*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
mm_hostbased_key_allowed(struct passwd *pw, const char *user, const char *host,
    struct sshkey *key)
{
	return (mm_key_allowed(MM_HOSTKEY, user, host, key, 0, NULL));
}