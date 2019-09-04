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
struct credential {int /*<<< orphan*/  password; int /*<<< orphan*/  username; } ;

/* Variables and functions */
 int /*<<< orphan*/  credential_write_item (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void credential_write(const struct credential *c)
{
	/* only write username/password, if set */
	credential_write_item(stdout, "username", c->username);
	credential_write_item(stdout, "password", c->password);
}