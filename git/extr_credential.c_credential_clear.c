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
struct credential {int /*<<< orphan*/  helpers; int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  path; int /*<<< orphan*/  host; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  credential_init (struct credential*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void credential_clear(struct credential *c)
{
	free(c->protocol);
	free(c->host);
	free(c->path);
	free(c->username);
	free(c->password);
	string_list_clear(&c->helpers, 0);

	credential_init(c);
}