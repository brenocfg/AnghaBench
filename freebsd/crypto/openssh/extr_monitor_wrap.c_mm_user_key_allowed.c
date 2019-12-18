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
struct sshauthopt {int dummy; } ;
struct ssh {int dummy; } ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MM_USERKEY ; 
 int mm_key_allowed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sshkey*,int,struct sshauthopt**) ; 

int
mm_user_key_allowed(struct ssh *ssh, struct passwd *pw, struct sshkey *key,
    int pubkey_auth_attempt, struct sshauthopt **authoptp)
{
	return (mm_key_allowed(MM_USERKEY, NULL, NULL, key,
	    pubkey_auth_attempt, authoptp));
}